* CMPL - Free-MPS - Export
NAME 07_Variablenprodukte
* OBJNAME p_bin
* OBJSENSE MAX
* OBJNAME p_int
* OBJSENSE MAX
* OBJNAME p_real
* OBJSENSE MAX
ROWS
 N p_bin
 N p_int
 N p_real
 L line_4
 L line_5
 G line_6
 E line_7
 L line_8
 L line_9
 G line_10
 L line_11
 L line_12
 G line_13
 L line_14
 L line_15
 G line_16
 L line_17
 L line_18
 G line_19
 E line_20
 E line_21
 E line_22
 L line_23
 L line_24
 G line_25
 E line_26
COLUMNS
 by line_5 -1 line_6 -1
 iy line_9 -1 line_10 -1
 iy line_12 -1 line_13 -1
 iy line_15 -1 line_16 -1
 iy line_18 -1 line_19 -1
 rx line_21 -1 line_26 -5.000000
 ry line_22 -1
 bx_by p_bin 1 line_4 1
 bx_by line_5 1 line_6 1
 ix_iy p_int 1 line_20 -1
 ix_b_iy[1] line_8 1 line_9 1
 ix_b_iy[1] line_10 1 line_20 1
 ix_b_iy[2] line_11 1 line_12 1
 ix_b_iy[2] line_13 1 line_20 2
 ix_b_iy[3] line_14 1 line_15 1
 ix_b_iy[3] line_16 1 line_20 4
 ix_b_iy[4] line_17 1 line_18 1
 ix_b_iy[4] line_19 1 line_20 8
 rx_n line_21 10.000000 line_23 -1
 rx_n line_25 -1
 ry_n line_22 20.000000 line_24 -1
 ry_n line_25 -1
 rx_ry_n line_23 1 line_24 1
 rx_ry_n line_25 1 line_26 -200.000000
 rx_ry p_real 1 line_26 1
 GVANF 'MARKER' 'INTORG'
 bx line_4 -25.000000 line_5 -5.000000
 bx line_6 -25.000000
 ix line_7 -1
 ix_b[1] line_7 1 line_8 -25.000000
 ix_b[1] line_9 -5.000000 line_10 -25.000000
 ix_b[2] line_7 2 line_11 -25.000000
 ix_b[2] line_12 -5.000000 line_13 -25.000000
 ix_b[3] line_7 4 line_14 -25.000000
 ix_b[3] line_15 -5.000000 line_16 -25.000000
 ix_b[4] line_7 8 line_17 -25.000000
 ix_b[4] line_18 -5.000000 line_19 -25.000000
 GVEND 'MARKER' 'INTEND'
RHS
 RHS line_5 -5.000000 line_6 -25.000000
 RHS line_9 -5.000000 line_10 -25.000000
 RHS line_12 -5.000000 line_13 -25.000000
 RHS line_15 -5.000000 line_16 -25.000000
 RHS line_18 -5.000000 line_19 -25.000000
 RHS line_22 -5.000000 line_25 -1
BOUNDS
 UP BOUND bx 1
 LO BOUND by 5.000000
 UP BOUND by 25.000000
 UP BOUND ix 10
 LO BOUND iy 5.000000
 UP BOUND iy 25.000000
 UP BOUND rx 10.000000
 LO BOUND ry 5.000000
 UP BOUND ry 25.000000
 UP BOUND bx_by 25.000000
 UP BOUND ix_b[1] 1
 UP BOUND ix_b[2] 1
 UP BOUND ix_b[3] 1
 UP BOUND ix_b[4] 1
 UP BOUND ix_iy 250.000000
 UP BOUND ix_b_iy[1] 25.000000
 UP BOUND ix_b_iy[2] 25.000000
 UP BOUND ix_b_iy[3] 25.000000
 UP BOUND ix_b_iy[4] 25.000000
 UP BOUND rx_n 1
 UP BOUND ry_n 1
 UP BOUND rx_ry_n 1
 UP BOUND rx_ry 250.000000
ENDATA
