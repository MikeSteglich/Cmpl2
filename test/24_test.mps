* CMPL - Free-MPS - Export
NAME 24_test
* OBJNAME profit
* OBJSENSE MAX
ROWS
 N profit
 L resaaaaaaaaa1[1]
 L resaaaaaaaaa1[2]
 L resaaaaaaaaa1[3]
 L __bb_a[1,1]
 G __bb_a[1,2]
 L __bb_a[2,1]
 G __bb_a[2,2]
 L __bb_a[3,1]
 G __bb_a[3,2]
COLUMNS
 x[1] profit 75 resaaaaaaaaa1[1] 8
 x[1] resaaaaaaaaa1[2] 15 resaaaaaaaaa1[3] 25
 x[1] __bb_a[1,1] -1 __bb_a[1,2] -1
 x[2] profit 80 resaaaaaaaaa1[1] 15
 x[2] resaaaaaaaaa1[2] 10 resaaaaaaaaa1[3] 16
 x[2] __bb_a[2,1] -1 __bb_a[2,2] -1
 x[3] profit 50 resaaaaaaaaa1[1] 12
 x[3] resaaaaaaaaa1[2] 8 resaaaaaaaaa1[3] 8
 x[3] __bb_a[3,1] -1 __bb_a[3,2] -1
 GVANF 'MARKER' 'INTORG'
 y[1] profit -500 __bb_a[1,1] 45
 y[1] __bb_a[1,2] 250
 y[2] profit -400 __bb_a[2,1] 45
 y[2] __bb_a[2,2] 240
 y[3] profit -500 __bb_a[3,1] 45
 y[3] __bb_a[3,2] 250
 GVEND 'MARKER' 'INTEND'
RHS
 RHS resaaaaaaaaa1[1] 1000 resaaaaaaaaa1[2] 1000
 RHS resaaaaaaaaa1[3] 1000
BOUNDS
 UP BOUND x[1] 250.000000
 UP BOUND x[2] 240.000000
 UP BOUND x[3] 250.000000
 UP BOUND y[1] 1
 UP BOUND y[2] 1
 UP BOUND y[3] 1
ENDATA
