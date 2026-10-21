#!/usr/bin/env python3
#
# Baut eine CMPL-Distribution fuer das Betriebssystem, auf dem das Skript
# laeuft (Windows, Linux oder macOS):
#
#   1. cmpl aus src/ kompilieren (in einer Kopie unter dist/build, damit
#      Objekte und bin/cmpl des Arbeitsstands unberuehrt bleiben)
#   2. HiGHS als statisches Binary von github.com/ERGO-Code/HiGHS holen
#   3. cmplStarter mit Nuitka zu einem eigenstaendigen Binary bauen
#   4. CmplIde (Flutter) bauen
#   5. alles zusammenstellen, testen und als Archiv nach dist/out packen
#
# Ein Cross-Build ist nicht moeglich (Flutter und Nuitka bauen nur fuer das
# eigene System), fuer drei Plattformen laeuft das Skript also dreimal.
#
# Aufruf:  python3 dist/buildDist.py [Optionen]      (Optionen: --help)
#
# Voraussetzungen siehe dist/README.md.

import argparse
import os
import platform
import re
import shutil
import stat
import subprocess
import sys
import tarfile
import urllib.request
import zipfile
from pathlib import Path

DISTDIR = Path(__file__).resolve().parent
CMPLDIR = DISTDIR.parent
PROJECTS = CMPLDIR.parent
RESOURCES = DISTDIR / "resources"

HIGHS_VERSION = "1.15.1"
HIGHS_URL = "https://github.com/ERGO-Code/HiGHS/releases/download/v{ver}/highs-{ver}-{asset}"
PYCMPL_REPO = "https://github.com/MikeSteglich/pyCmpl.git"
PYCMPL_DEFAULT = "v3.0.0"

# Dateien aus Cmpl2/bin, die unveraendert in die Distribution gehen
BIN_FILES = ["modules.opt", "solversel.opt", "cmplstd.cmpl", "gurobiCmpl.py"]

# Visual C++ Runtime, die eine Flutter-Windows-App braucht, aber nicht mitbringt
VC_RUNTIME = ["msvcp140.dll", "vcruntime140.dll", "vcruntime140_1.dll"]

SMOKE_MODEL = """\
variables:
    x[1..2]: integer[0..];
objectives:
    profit: 3*x[1] + 2*x[2] -> max;
constraints:
    x[1] + x[2] <= 4;
    x[1] + 3*x[2] <= 6;
    x[1] <= 3;
"""


class BuildError(Exception):
    pass


# ---------------------------------------------------------------- Hilfen

def log(msg):
    print("\n==> " + msg, flush=True)


def run(cmd, cwd=None, env=None, capture=False):
    print("    $ " + " ".join(str(c) for c in cmd), flush=True)
    try:
        res = subprocess.run([str(c) for c in cmd], cwd=cwd, env=env, text=True,
                             stdout=subprocess.PIPE if capture else None,
                             stderr=subprocess.STDOUT if capture else None)
    except FileNotFoundError:
        raise BuildError(f"Programm nicht gefunden: {cmd[0]}")
    if res.returncode != 0:
        if capture:
            print(res.stdout)
        raise BuildError(f"Fehlgeschlagen ({res.returncode}): {' '.join(str(c) for c in cmd)}")
    return res.stdout if capture else None


def which(*names):
    for n in names:
        p = shutil.which(n)
        if p:
            return p
    return None


def make_executable(path):
    path.chmod(path.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)


def copy_tree(src, dst):
    shutil.copytree(src, dst, symlinks=True, dirs_exist_ok=True)


class Target:
    """Betriebssystem und Architektur, fuer die gebaut wird (= das eigene)."""

    def __init__(self):
        s = platform.system()
        self.os = {"Darwin": "macos", "Windows": "windows", "Linux": "linux"}.get(s)
        if not self.os:
            raise BuildError(f"Nicht unterstuetztes System: {s}")
        m = platform.machine().lower()
        self.arch = {"amd64": "x86_64", "x64": "x86_64", "aarch64": "arm64"}.get(m, m)
        self.exe = ".exe" if self.is_win else ""

    is_win = property(lambda self: self.os == "windows")
    is_mac = property(lambda self: self.os == "macos")
    is_linux = property(lambda self: self.os == "linux")

    def __str__(self):
        return f"{self.os}-{self.arch}"


def cmpl_version():
    hh = (CMPLDIR / "src/Control/MainControl.hh").read_text(errors="replace")
    m = re.search(r'#define\s+CMPL_VERSION\s+"([^"]+)"', hh)
    return m.group(1) if m else "unknown"


# ---------------------------------------------------------------- 1. cmpl

def build_cmpl(t, work, args):
    log("cmpl kompilieren")
    src = work / "src"
    if args.clean and src.exists():
        shutil.rmtree(src)
    # Kopie ohne Objekte; copy2 behaelt die Zeitstempel, so dass ein
    # erneuter Lauf inkrementell baut
    shutil.copytree(CMPLDIR / "src", src, dirs_exist_ok=True,
                    ignore=shutil.ignore_patterns("*.o", "*.d", ".DS_Store"))

    make = which("make", "mingw32-make") if t.is_win else which("make")
    if not make:
        raise BuildError("make nicht gefunden" + (" (MSYS2/MinGW installieren)" if t.is_win else ""))

    cxx = os.environ.get("CXX") or ("clang++" if t.is_mac else "g++")
    cxxflags = "-std=c++14 -O2 -DSTANDALONE -DPROTO -DCHDIR -w"
    libs = ""
    if t.is_mac:
        cxxflags += " -mmacosx-version-min=11.0"
        libs = "-mmacosx-version-min=11.0"
    elif t.is_linux:
        libs = "-static-libstdc++ -static-libgcc"
    elif t.is_win:
        libs = "-static"

    out = work / "cmpl-bin" / "cmpl"
    out.parent.mkdir(parents=True, exist_ok=True)
    run([make, "-C", src, f"-j{args.jobs}", f"CXX={cxx}", f"CXXFLAGS={cxxflags}",
         f"LIBS={libs}", f"OUTPUT={out.as_posix()}"])

    binary = out.with_name("cmpl" + t.exe)
    if not binary.exists():
        raise BuildError(f"cmpl-Binary nicht entstanden: {binary}")
    if not t.is_win:
        run(["strip", binary] if t.is_linux else ["strip", "-x", binary])
    return binary


# ---------------------------------------------------------------- 2. HiGHS

def highs_asset(t):
    if t.is_mac:
        return "arm-apple-static-mit.tar.gz"          # universal: arm64 + x86_64
    a = {"x86_64": "x86_64", "arm64": "aarch64"}.get(t.arch)
    if not a:
        raise BuildError(f"Kein HiGHS-Binary fuer {t}, bitte --highs angeben")
    if t.is_linux:
        return f"{a}-linux-gnu-static-mit.tar.gz"
    return f"{a}-windows-static-mit.zip"


def fetch_highs(t, work, args):
    """Liefert das Verzeichnis mit highs(.exe) und den Lizenzdateien."""
    dest = work / "highs"
    if dest.exists():
        shutil.rmtree(dest)
    dest.mkdir(parents=True)

    if args.highs:
        log(f"HiGHS aus {args.highs}")
        src = Path(args.highs)
        shutil.copy2(src, dest / ("highs" + t.exe))
        for f in ("LICENSE.txt", "README.md", "AUTHORS"):
            if (src.parent / f).exists():
                shutil.copy2(src.parent / f, dest / f)
        return dest

    asset = highs_asset(t)
    url = HIGHS_URL.format(ver=args.highs_version, asset=asset)
    cache = DISTDIR / "cache" / f"highs-{args.highs_version}-{asset}"
    if not cache.exists():
        log(f"HiGHS {args.highs_version} laden: {url}")
        cache.parent.mkdir(parents=True, exist_ok=True)
        tmp = cache.with_suffix(".part")
        try:
            with urllib.request.urlopen(url) as r, open(tmp, "wb") as f:
                shutil.copyfileobj(r, f)
        except OSError as e:
            raise BuildError(f"Download fehlgeschlagen: {url}: {e}")
        tmp.rename(cache)
    else:
        log(f"HiGHS {args.highs_version} aus dem Cache: {cache.name}")

    # nur die benoetigten Dateien auspacken (keine Pfade aus dem Archiv uebernehmen)
    wanted = {f"bin/highs{t.exe}": "highs" + t.exe,
              "share/doc/HIGHS/LICENSE.txt": "LICENSE.txt",
              "share/doc/HIGHS/README.md": "README.md",
              "share/doc/HIGHS/AUTHORS": "AUTHORS"}
    found = set()
    if asset.endswith(".zip"):
        with zipfile.ZipFile(cache) as z:
            for name in z.namelist():
                key = name.lstrip("./")
                if key in wanted:
                    (dest / wanted[key]).write_bytes(z.read(name))
                    found.add(key)
    else:
        with tarfile.open(cache) as tf:
            for m in tf.getmembers():
                key = m.name.lstrip("./")
                if key in wanted and m.isfile():
                    (dest / wanted[key]).write_bytes(tf.extractfile(m).read())
                    found.add(key)
    if f"bin/highs{t.exe}" not in found:
        raise BuildError(f"bin/highs{t.exe} nicht in {cache.name}")
    if not t.is_win:
        make_executable(dest / "highs")
    return dest


# ---------------------------------------------------------------- 3. pyCmpl + cmplStarter

def stage_pycmpl(work, args):
    """Legt pyCmpl/lib3/pyCmpl und pyCmpl/lib3/cmplServer an."""
    lib3 = work / "pyCmpl" / "lib3"
    if lib3.exists():
        shutil.rmtree(lib3)
    target = lib3 / "pyCmpl"
    target.mkdir(parents=True)

    spec = args.pycmpl
    if Path(spec).is_dir():
        src = Path(spec) / "pyCmpl"
        try:
            desc = subprocess.run(["git", "-C", spec, "describe", "--tags", "--always", "--dirty"],
                                  capture_output=True, text=True).stdout.strip() or "?"
        except FileNotFoundError:
            desc = "?"
        version = f"lokal: {Path(spec).resolve()} ({desc})"
        log(f"pyCmpl {version}")
    else:
        log(f"pyCmpl {spec} aus {PYCMPL_REPO}")
        clone = work / "pyCmpl-src"
        if clone.exists():
            shutil.rmtree(clone)
        run(["git", "clone", "-q", "--depth", "1", "--branch", spec, PYCMPL_REPO, clone])
        src = clone / "pyCmpl"
        version = spec

    if not (src / "Cmpl.py").exists():
        raise BuildError(f"Keine pyCmpl-Quellen gefunden: {src}")
    for f in src.glob("*.py"):
        shutil.copy2(f, target / f.name)
    (target / "PYCMPL_VERSION").write_text(version + "\n")

    server = Path(args.cmplserver)
    if not (server / "cmplServerHandler.py").exists():
        raise BuildError(f"cmplServer-Quellen nicht gefunden: {server} (--cmplserver)")
    (lib3 / "cmplServer").mkdir()
    for f in server.glob("*.py"):
        shutil.copy2(f, lib3 / "cmplServer" / f.name)
    return work / "pyCmpl"


def nuitka_build(t, work, pycmpl, args, name, script, packages):
    """Kompiliert script mit Nuitka zu <name>.dist/<name>[.exe]."""
    log(f"{name} mit Nuitka bauen")
    py = args.nuitka_python
    try:
        run([py, "-m", "nuitka", "--version"], capture=True)
    except BuildError:
        raise BuildError(f"Nuitka laeuft nicht mit {py} - bitte --nuitka-python setzen "
                         "(z.B. conda create -n nuitka python nuitka xlwings)")

    out = work / "nuitka" / name
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    # Dateiname bleibt (cmplServerHandler.py heisst nicht wie das Paket
    # cmplServer, das es importiert), nur das Binary bekommt den neuen Namen
    src = out / Path(script).name
    shutil.copy2(script, src)

    env = dict(os.environ, PYTHONPATH=str(pycmpl / "lib3"))
    if t.is_mac:
        # install_name_tool/codesign von Xcode, nicht die aus Anaconda
        env["PATH"] = "/usr/bin:/bin:/usr/sbin:/sbin"

    run([py, "-m", "nuitka", "--standalone", "--assume-yes-for-downloads",
         *[f"--include-package={p}" for p in packages],
         "--nofollow-import-to=pandas", "--nofollow-import-to=numpy",
         "--nofollow-import-to=PIL", "--nofollow-import-to=matplotlib",
         "--nofollow-import-to=tkinter", "--nofollow-import-to=pytest",
         f"--output-dir={out}", f"--output-filename={name}", "--remove-output",
         "--company-name=TH Wildau", "--product-name=CMPL",
         f"--product-version={cmpl_version()}",
         src], env=env)

    dist = out / f"{src.stem}.dist"
    if src.stem != name and dist.exists():
        dist = dist.rename(out / f"{name}.dist")
    if not (dist / (name + t.exe)).exists():
        raise BuildError(f"Nuitka hat kein {name}{t.exe} erzeugt")
    return dist


def build_starter(t, work, pycmpl, args):
    return nuitka_build(t, work, pycmpl, args, "cmplStarter",
                        RESOURCES / "cmplStarter.py", ["pyCmpl"])


def build_server(t, work, pycmpl, args):
    return nuitka_build(t, work, pycmpl, args, "cmplServer",
                        pycmpl / "lib3/cmplServer/cmplServerHandler.py",
                        ["pyCmpl", "cmplServer"])


# ---------------------------------------------------------------- 4. CmplIde

def build_ide(t, args):
    """Liefert das gebaute IDE-Bundle (.app bzw. Verzeichnis mit cmpl_ide[.exe])."""
    if args.ide_bundle:
        log(f"CmplIde aus {args.ide_bundle}")
        return Path(args.ide_bundle)

    ide = Path(args.ide_src)
    if not (ide / "pubspec.yaml").exists():
        raise BuildError(f"CmplIde-Quellen nicht gefunden: {ide} (--ide-src oder --no-ide)")
    flutter = args.flutter or which("flutter")
    if not flutter:
        raise BuildError("flutter nicht gefunden (--flutter)")

    log(f"CmplIde bauen ({ide})")
    env = dict(os.environ)
    # Die Xcode-Phase "Bundle CMPL Runtime" wuerde sonst die Laufzeit aus
    # pyCmplBin einbetten - das uebernimmt hier assemble()
    env["CMPL_BUNDLER"] = str(DISTDIR / "no-bundler")
    if args.clean:
        run([flutter, "clean"], cwd=ide, env=env)
    run([flutter, "pub", "get"], cwd=ide, env=env)
    run([flutter, "build", t.os, "--release", f"--build-name={cmpl_version()}"], cwd=ide, env=env)

    if t.is_mac:
        apps = sorted((ide / "build/macos/Build/Products/Release").glob("*.app"))
        if not apps:
            raise BuildError("Keine .app nach flutter build macos gefunden")
        return apps[0]
    arch = "arm64" if t.arch == "arm64" else "x64"
    bundle = (ide / f"build/windows/{arch}/runner/Release") if t.is_win \
        else (ide / f"build/linux/{arch}/release/bundle")
    if not bundle.is_dir():
        raise BuildError(f"IDE-Bundle nicht gefunden: {bundle}")
    return bundle


# ---------------------------------------------------------------- 5. Zusammenstellen

def assemble_runtime(t, root, cmpl_bin, highs, pycmpl, starter, server, args):
    """CMPL-Laufzeit: cmpl- und cmplServer-Startskript, bin/, Thirdparty/Highs, pyCmpl/, doc/."""
    bin_ = root / "bin"
    bin_.mkdir(parents=True)

    shutil.copy2(cmpl_bin, bin_ / cmpl_bin.name)
    shutil.copy2(RESOURCES / f"cmpl.opt.{t.os}", bin_ / "cmpl.opt")
    for f in BIN_FILES:
        shutil.copy2(CMPLDIR / "bin" / f, bin_ / f)

    # auf dem CmplServer nur die Solver anbieten, die auch dabei sind
    opt = (CMPLDIR / "bin/cmplServer.opt").read_text()
    opt = re.sub(r"(?m)^solvers\s*=.*$", "solvers = highs", opt)
    (bin_ / "cmplServer.opt").write_text(opt)

    if t.is_win:
        for f in ("cmpl.bat", "cmplServer.bat"):
            shutil.copy2(RESOURCES / f, root / f)
        shutil.copy2(RESOURCES / "gurobiCmpl.bat", bin_ / "gurobiCmpl.bat")
    else:
        for src, dst in ((RESOURCES / "cmpl", root / "cmpl"),
                         (RESOURCES / "cmplServer", root / "cmplServer"),
                         (CMPLDIR / "bin/gurobiCmpl", bin_ / "gurobiCmpl"),
                         (RESOURCES / "manual", bin_ / "manual")):
            shutil.copy2(src, dst)
            make_executable(dst)

    # ohne Nuitka-Build laufen cmplStarter und cmplServer aus den Quellen (mit Python)
    if starter:
        copy_tree(starter, bin_ / "cmplStarter.dist")
    else:
        shutil.copy2(RESOURCES / "cmplStarter.py", bin_ / "cmplStarter.py")
    if server:
        copy_tree(server, bin_ / "cmplServer.dist")

    copy_tree(highs, root / "Thirdparty" / "Highs")
    copy_tree(pycmpl, root / "pyCmpl")

    if args.manual:
        (root / "doc").mkdir()
        shutil.copy2(args.manual, root / "doc" / "CMPL.pdf")


def assemble_core(t, stage, cmpl_bin, highs):
    """Nur der CMPL-Kern, wie ihn pyCmpl ueber CMPLHOME braucht:
    bin/cmpl + *.opt + cmplstd.cmpl und Thirdparty/Highs - ohne Startskripte,
    cmplStarter, cmplServer, pyCmpl und IDE."""
    log(f"CMPL-Kern zusammenstellen: {stage}")
    if stage.exists():
        shutil.rmtree(stage)
    bin_ = stage / "bin"
    bin_.mkdir(parents=True)
    shutil.copy2(cmpl_bin, bin_ / cmpl_bin.name)
    shutil.copy2(RESOURCES / f"cmpl.opt.{t.os}", bin_ / "cmpl.opt")
    for f in ("modules.opt", "solversel.opt", "cmplstd.cmpl"):
        shutil.copy2(CMPLDIR / "bin" / f, bin_ / f)
    copy_tree(highs, stage / "Thirdparty" / "Highs")
    for f in ("LICENSE", "AUTHORS"):
        shutil.copy2(CMPLDIR / f, stage / f)


def smoke_test_core(t, stage, work):
    log("Test: Modell direkt mit bin/cmpl und HiGHS loesen")
    tdir = work / "smoketest"
    if tdir.exists():
        shutil.rmtree(tdir)
    tdir.mkdir()
    (tdir / "smoke.cmpl").write_text(SMOKE_MODEL)
    out = run([stage / "bin" / ("cmpl" + t.exe), "smoke.cmpl", "-solver", "highs"], cwd=tdir, capture=True)
    check_smoke_result(out, "CMPL-Kern")


def add_docs(dest):
    for f in ("README.md", "LICENSE", "AUTHORS"):
        shutil.copy2(CMPLDIR / f, dest / f)


def copy_vc_runtime(dest):
    sysdir = Path(os.environ.get("SystemRoot", r"C:\Windows")) / "System32"
    for dll in VC_RUNTIME:
        if (sysdir / dll).exists():
            shutil.copy2(sysdir / dll, dest / dll)
        else:
            print(f"    WARNUNG: {dll} nicht gefunden - IDE braucht dann das VC++ Redistributable")


def is_macho(path):
    try:
        with open(path, "rb") as f:
            magic = f.read(4)
    except OSError:
        return False
    return magic in (b"\xcf\xfa\xed\xfe", b"\xce\xfa\xed\xfe", b"\xca\xfe\xba\xbe",
                     b"\xfe\xed\xfa\xcf", b"\xfe\xed\xfa\xce")


def codesign_file(opts, identity, f):
    # codesign meldet gelegentlich "internal error in Code Signing subsystem" - ein zweiter Versuch klappt
    for attempt in range(3):
        try:
            return run(["codesign", *opts, "--sign", identity, f], capture=True)
        except BuildError:
            if attempt == 2:
                raise


def codesign_app(app, args):
    identity = args.sign or os.environ.get("CMPL_CODESIGN_IDENTITY") or "-"
    log(f"App signieren (Identitaet: {identity})")
    opts = ["--force"]
    if identity != "-":
        opts += ["--options", "runtime", "--timestamp"]
    run(["xattr", "-cr", app])

    # von innen nach aussen: erst die eingebetteten Binaries der Laufzeit ...
    runtime = app / "Contents/Resources/cmpl"
    for f in sorted(runtime.rglob("*")):
        if f.is_file() and not f.is_symlink() and is_macho(f):
            codesign_file(opts, identity, f)

    # ... dann das Bundle selbst, mit den Entitlements der IDE
    ent = Path(args.ide_src) / "macos/Runner/Release.entitlements"
    if ent.exists():
        opts += ["--entitlements", ent]
    run(["codesign", *opts, "--sign", identity, app])
    run(["codesign", "--verify", "--deep", "--strict", app])


def assemble(t, stage, cmpl_bin, highs, pycmpl, starter, server, ide, args):
    log(f"Distribution zusammenstellen: {stage}")
    if stage.exists():
        shutil.rmtree(stage)
    stage.mkdir(parents=True)

    if t.is_mac:
        # Laufzeit in die App, damit sie auch nach App Translocation
        # (Start aus Downloads/Quarantaene) vollstaendig ist
        if ide:
            app = stage / ide.name
            run(["ditto", ide, app])
            runtime = app / "Contents/Resources/cmpl"
            if runtime.exists():
                # Rest einer frueheren Einbettung (bundleCmplIntoApp.sh) im Flutter-Build
                shutil.rmtree(runtime)
            assemble_runtime(t, runtime, cmpl_bin, highs, pycmpl, starter, server, args)
            for script in ("cmpl", "cmplServer"):
                launcher = (RESOURCES / "cmpl.macos").read_text() \
                    .replace("@IDE_APP@", app.name).replace("@SCRIPT@", script)
                (stage / script).write_text(launcher)
                make_executable(stage / script)
            codesign_app(app, args)
            runtime_root = runtime
        else:
            assemble_runtime(t, stage, cmpl_bin, highs, pycmpl, starter, server, args)
            runtime_root = stage
    else:
        # Windows/Linux: die IDE sucht cmpl(.bat) im Verzeichnis ueber ihrem Programm
        assemble_runtime(t, stage, cmpl_bin, highs, pycmpl, starter, server, args)
        runtime_root = stage
        if ide:
            copy_tree(ide, stage / "CmplIde")
            if t.is_win:
                copy_vc_runtime(stage / "CmplIde")

    add_docs(stage)
    for junk in list(stage.rglob(".DS_Store")) + list(stage.rglob("__pycache__")):
        shutil.rmtree(junk) if junk.is_dir() else junk.unlink()
    return runtime_root


# ---------------------------------------------------------------- Test und Archiv

def check_smoke_result(out, what):
    print("    " + "\n    ".join(out.strip().splitlines()[-8:]))
    if not re.search(r"Objective value\s+11\b", out) or "OPTIMAL" not in out:
        raise BuildError(f"Test fehlgeschlagen ({what}): erwartet Zielfunktionswert 11 (optimal)\n" + out)
    print("    ok")


def smoke_test(t, runtime_root, work, port):
    tdir = work / "smoketest"
    if tdir.exists():
        shutil.rmtree(tdir)
    tdir.mkdir()
    (tdir / "smoke.cmpl").write_text(SMOKE_MODEL)
    cmpl = [runtime_root / "cmpl.bat"] if t.is_win else ["/bin/bash", runtime_root / "cmpl"]

    log("Test: Modell ueber das cmpl-Startskript mit HiGHS loesen")
    out = run(cmpl + ["smoke.cmpl", "-solver", "highs"], cwd=tdir, capture=True)
    check_smoke_result(out, "lokal")

    # Server direkt starten (das Startskript laesst ihn unter Windows im
    # Vordergrund laufen), Modell mit -url loesen, Server wieder stoppen
    log(f"Test: CmplServer auf Port {port} starten und Modell mit -url loesen")
    server = runtime_root / "bin/cmplServer.dist" / ("cmplServer" + t.exe)
    if server.exists():
        server_cmd = [server]
    else:
        server_cmd = [sys.executable, runtime_root / "pyCmpl/lib3/cmplServer/cmplServerHandler.py"]
    env = dict(os.environ, CMPLHOME=str(runtime_root) + os.sep,
               PYTHONPATH=str(runtime_root / "pyCmpl/lib3"))
    proc = subprocess.Popen([str(c) for c in server_cmd + ["-start", str(port)]], env=env,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    try:
        url = f"http://127.0.0.1:{port}"
        for _ in range(30):
            if proc.poll() is not None:
                raise BuildError("CmplServer hat sich beendet:\n" + proc.stdout.read())
            st = subprocess.run([str(c) for c in server_cmd + ["-status", str(port)]], env=env,
                                capture_output=True, text=True).stdout
            if "is running" in st:
                break
            subprocess.run([sys.executable, "-c", "import time; time.sleep(1)"])
        else:
            raise BuildError("CmplServer meldet sich nicht")
        # -solver ausdruecklich: pyCmpl schickt sonst cbc als Default an den Server
        out = run(cmpl + ["smoke.cmpl", "-url", url, "-solver", "highs"], cwd=tdir, capture=True)
        check_smoke_result(out, "CmplServer")
    finally:
        subprocess.run([str(c) for c in server_cmd + ["-stop", str(port)]], env=env,
                       capture_output=True)
        try:
            proc.wait(timeout=15)
        except subprocess.TimeoutExpired:
            proc.kill()


def pack(t, stage, name):
    outdir = DISTDIR / "out"
    outdir.mkdir(exist_ok=True)
    log("Archiv packen")
    if t.is_linux:
        archive = outdir / f"{name}.tar.gz"
        with tarfile.open(archive, "w:gz") as tf:
            tf.add(stage, arcname=stage.name)
    elif t.is_mac:
        # ditto erhaelt Rechte, Symlinks und Signaturen
        archive = outdir / f"{name}.zip"
        if archive.exists():
            archive.unlink()
        run(["ditto", "-c", "-k", "--sequesterRsrc", "--keepParent", stage, archive])
    else:
        archive = Path(shutil.make_archive(str(outdir / name), "zip", stage.parent, stage.name))
    print(f"    {archive}  ({archive.stat().st_size / 1e6:.1f} MB)")
    return archive


# ---------------------------------------------------------------- main

def main():
    ap = argparse.ArgumentParser(
        description="Baut die CMPL-Distribution (cmpl, HiGHS, cmplStarter, CmplIde) "
                    "fuer das aktuelle Betriebssystem.")
    ap.add_argument("--core", action="store_true",
                    help="nur den CMPL-Kern bauen (bin/cmpl, *.opt, Thirdparty/Highs) - fuer "
                         "Anwendungen, die pyCmpl mit CMPLHOME nutzen, z.B. pyLogisticsLab")
    ap.add_argument("--stage", metavar="DIR",
                    help="Verzeichnis, in dem die Distribution zusammengestellt wird "
                         "(Default: dist/build/<os>-<arch>/Cmpl2 bzw. .../cmpl-core)")
    ap.add_argument("--clean", action="store_true",
                    help="alles neu bauen (cmpl-Objekte, flutter clean)")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 2,
                    help="parallele Compiler-Jobs (Default: Anzahl CPUs)")
    ap.add_argument("--highs-version", default=HIGHS_VERSION,
                    help=f"HiGHS-Release von GitHub (Default: {HIGHS_VERSION})")
    ap.add_argument("--highs", metavar="BINARY",
                    help="eigenes highs-Binary statt Download")
    ap.add_argument("--pycmpl", default=PYCMPL_DEFAULT, metavar="TAG|DIR",
                    help=f"pyCmpl: Git-Tag aus {PYCMPL_REPO} oder lokales Repository "
                         f"(Default: {PYCMPL_DEFAULT})")
    ap.add_argument("--cmplserver", default=str(PROJECTS / "pyCmplBin/pyCmpl/lib3/cmplServer"),
                    metavar="DIR", help="cmplServer-Quellen (Default: %(default)s)")
    ap.add_argument("--test-port", type=int, default=8123,
                    help="Port fuer den CmplServer-Test (Default: %(default)s)")
    ap.add_argument("--nuitka-python", default=os.environ.get("NUITKA_PYTHON", sys.executable),
                    metavar="PYTHON", help="Python mit Nuitka (Default: $NUITKA_PYTHON oder dieses Python)")
    ap.add_argument("--no-starter", action="store_true",
                    help="cmplStarter und cmplServer nicht kompilieren, nur die Python-Quellen "
                         "beilegen (braucht dann Python)")
    ap.add_argument("--ide-src", default=str(PROJECTS / "CmplIde"), metavar="DIR",
                    help="Flutter-Projekt der CmplIde (Default: %(default)s)")
    ap.add_argument("--ide-bundle", metavar="PATH",
                    help="schon gebaute IDE (.app bzw. Release-/bundle-Verzeichnis) verwenden")
    ap.add_argument("--no-ide", action="store_true", help="Distribution ohne IDE")
    ap.add_argument("--flutter", metavar="FLUTTER", help="flutter-Programm (Default: aus PATH)")
    ap.add_argument("--manual", metavar="PDF", help="Handbuch als doc/CMPL.pdf beilegen")
    ap.add_argument("--sign", metavar="IDENTITY",
                    help="macOS: Signatur-Identitaet (Default: $CMPL_CODESIGN_IDENTITY oder ad hoc)")
    ap.add_argument("--no-test", action="store_true", help="Test-Modell nicht loesen")
    ap.add_argument("--no-archive", action="store_true", help="nur dist/build/.../Cmpl2 anlegen")
    args = ap.parse_args()

    t = Target()
    version = cmpl_version()
    work = DISTDIR / "build" / str(t)
    print(f"CMPL {version} - {'Kern' if args.core else 'Distribution'} fuer {t}")
    work.mkdir(parents=True, exist_ok=True)

    cmpl_bin = build_cmpl(t, work, args)
    highs = fetch_highs(t, work, args)

    if args.core:
        stage = Path(args.stage).resolve() if args.stage else work / "cmpl-core"
        assemble_core(t, stage, cmpl_bin, highs)
        if not args.no_test:
            smoke_test_core(t, stage, work)
        if not args.no_archive:
            pack(t, stage, f"Cmpl-core-{version}-{t}")
        log(f"Fertig: {stage}")
        return

    stage = Path(args.stage).resolve() if args.stage else work / "Cmpl2"
    name = f"Cmpl-{version}-{t}"
    pycmpl = stage_pycmpl(work, args)
    starter = None if args.no_starter else build_starter(t, work, pycmpl, args)
    server = None if args.no_starter else build_server(t, work, pycmpl, args)
    ide = None if args.no_ide else build_ide(t, args)

    runtime_root = assemble(t, stage, cmpl_bin, highs, pycmpl, starter, server, ide, args)
    if not args.no_test:
        smoke_test(t, runtime_root, work, args.test_port)
    if not args.no_archive:
        pack(t, stage, name)
    log(f"Fertig: {stage}")


if __name__ == "__main__":
    try:
        main()
    except BuildError as e:
        print(f"\nFEHLER: {e}", file=sys.stderr)
        sys.exit(1)
    except KeyboardInterrupt:
        sys.exit(130)
