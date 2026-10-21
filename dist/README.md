# CMPL-Distribution bauen

`buildDist.py` baut eine vollstaendige CMPL-Distribution fuer das System, auf dem es laeuft:

1. **cmpl** aus `src/` kompilieren (in einer Kopie unter `dist/build/`, der Arbeitsstand mit `bin/cmpl` bleibt unberuehrt)
2. **HiGHS** als statisches Binary vom [HiGHS-Release](https://github.com/ERGO-Code/HiGHS/releases) laden (Cache in `dist/cache/`)
3. **cmplStarter** und **cmplServer** mit Nuitka zu eigenstaendigen Binaries kompilieren, damit kein Python mitgeliefert werden muss
4. **CmplIde** (Flutter) bauen
5. alles zusammenstellen, testen und nach `dist/out/` packen. Der Test loest ein Modell lokal mit HiGHS und ueber einen kurz gestarteten CmplServer (`-url`, Port `--test-port`, Default 8123).

Flutter und Nuitka koennen nicht cross-compilieren. Fuer Windows, Linux und macOS laeuft das Skript also jeweils auf dem entsprechenden System.

```bash
python3 dist/buildDist.py                  # alles
python3 dist/buildDist.py --clean          # alles neu bauen
python3 dist/buildDist.py --no-ide         # nur die CMPL-Laufzeit
python3 dist/buildDist.py --core           # nur der CMPL-Kern: bin/cmpl, *.opt, Thirdparty/Highs
python3 dist/buildDist.py --help           # alle Optionen
```

Ergebnis: `dist/out/Cmpl-<version>-<os>-<arch>.zip` (Linux: `.tar.gz`), ausgepackt unter `dist/build/<os>-<arch>/Cmpl2/`.

Der **Kern** (`--core`) ist fuer Anwendungen gedacht, die pyCmpl mit `CMPLHOME` nutzen, z.B. pyLogisticsLab. Er enthaelt weder Startskripte noch cmplStarter, cmplServer, pyCmpl oder IDE, und Nuitka und Flutter werden dafuer nicht gebraucht. Mit `--stage DIR` wird er direkt in ein anderes Verzeichnis gelegt.

## Voraussetzungen

| | alle Systeme | Windows | Linux | macOS |
|---|---|---|---|---|
| cmpl | `make`, C++14-Compiler | MSYS2 mit MinGW-w64 (`g++`, `make` im PATH) | `g++`, `make` | Xcode Command Line Tools |
| cmplStarter | Python mit `nuitka` (und `xlwings` fuer CmplXlsData) | | | |
| cmplServer | `../pyCmplBin/pyCmpl/lib3/cmplServer` | `--cmplserver DIR` |
| CmplIde | Flutter, IDE-Quellen unter `../CmplIde` | Visual Studio mit C++-Workload | GTK-3-Entwicklungspakete, `clang`, `cmake`, `ninja` | Xcode |
| sonst | `git` (pyCmpl-Tag klonen), Internet (HiGHS-Download) | | | |

Das Python fuer Nuitka wird mit `--nuitka-python` oder `$NUITKA_PYTHON` gesetzt, sonst nimmt das Skript das Python, mit dem es gestartet wurde. Auf dem Mac z.B.:

```bash
/opt/anaconda3/envs/nuitka/bin/python dist/buildDist.py
```

## Inhalt der Distribution

```
Cmpl2/                         Windows / Linux
  cmpl | cmpl.bat              Startskript (setzt CMPLHOME, ruft cmplStarter)
  cmplServer | cmplServer.bat  CmplServer starten/stoppen: -start, -startInGrid, -startScheduler, -stop, -status
  bin/
    cmpl[.exe]                 statisch gelinkt (libstdc++/libgcc bzw. -static unter MinGW)
    cmplStarter.dist/          Nuitka-Build
    cmplServer.dist/           Nuitka-Build
    cmpl.opt                   Solverpfade, relativ zu bin/
    cmplServer.opt             Port, maxProblems ... (solvers = highs)
    modules.opt solversel.opt cmplstd.cmpl gurobiCmpl* manual
  Thirdparty/Highs/            highs[.exe] + Lizenz (MIT)
  pyCmpl/lib3/                 pyCmpl und cmplServer (Quellen)
  CmplIde/                     cmpl_ide[.exe] mit Flutter-Bibliotheken
                               (Windows: inkl. VC++-Runtime-DLLs)
  doc/CMPL.pdf                 nur mit --manual
  README.md LICENSE AUTHORS
```

Der CmplServer laeuft unter Unix mit `cmplServer -start [<port>]` im Hintergrund, unter Windows mit `cmplServer.bat -start [<port>]` im Vordergrund. Gestoppt wird er mit `-stop`. Logs und Problemdateien liegen in `~/CmplServer`. Geloest wird auf einem Server mit der CMPL-Option `-url http://<host>:<port>`, die IDE hat dafuer keine eigene Aktion mehr.

Die IDE sucht `cmpl` bzw. `cmpl.bat` im Verzeichnis ueber ihrem Programm, also in `Cmpl2/`.

Unter **macOS** liegt die ganze Laufzeit in der App (`cmpl_ide.app/Contents/Resources/cmpl/`). So funktioniert sie auch nach App Translocation, also wenn sie direkt aus dem Download-Ordner gestartet wird. `Cmpl2/cmpl` und `Cmpl2/cmplServer` sind kleine Wrapper fuer die Kommandozeile. Nach dem Einbetten wird die App neu signiert: ohne weitere Angabe ad hoc, mit `--sign "Developer ID Application: ..."` oder `$CMPL_CODESIGN_IDENTITY` mit einer Identitaet (dann mit Hardened Runtime). Die Notarisierung ist nicht Teil des Skripts.

## Quellen und Optionen

| | Default | Option |
|---|---|---|
| HiGHS | Release 1.15.1, Variante `static-mit` (macOS: Universal Binary) | `--highs-version`, `--highs BINARY` |
| pyCmpl | Tag `v2.1.0` aus github.com/MikeSteglich/pyCmpl | `--pycmpl TAG` oder `--pycmpl ../pyCmpl` (lokal) |
| cmplServer | `../pyCmplBin/pyCmpl/lib3/cmplServer` | `--cmplserver DIR` |
| CmplIde | `../CmplIde` | `--ide-src DIR`, `--ide-bundle PATH`, `--no-ide` |
| Handbuch | keins | `--manual CMPL.pdf` |

Die Startskripte und `cmpl.opt`-Vorlagen fuer die Distribution liegen in `dist/resources/`.
