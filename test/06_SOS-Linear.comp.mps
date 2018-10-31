* CMPL - Free-MPS - Export
NAME 06_SOS-Linear
ROWS
 G line_1
 G line_2
 G line_3
 G line_4
 G line_5
 L x_sos[1]
 G line_7
 G line_8
 G line_9
 G line_10
 G line_11
 G line_12
 G line_13
 G line_14
 G line_15
 G line_16
 L testB
 L line_18
 L line_19
 L line_20
 L line_21
 L line_22
 L line_23
 L line_24
 L line_25
 L line_26
 L line_27
 L testB_sos2
 G line_29
 G line_30
 G line_31
 L testC
 L SOS_Row_1
 L SOS_Row_2
 L SOS_Row_3
 L SOS_Col_1
 L SOS_Col_2
 L SOS_Col_3
 L SOS_Col_4
COLUMNS
 x[1] line_1 -1
 x[2] line_2 -1
 x[3] line_3 -1
 x[4] line_4 -1
 x[5] line_5 -1
 y[1] line_7 -1
 y[2] line_8 -1
 y[3] line_9 -1
 y[4] line_10 -1
 y[5] line_11 -1
 y[6] line_12 -1
 y[7] line_13 -1
 y[8] line_14 -1
 y[9] line_15 -1
 y[10] line_16 -1
 GVANF 'MARKER' 'INTORG'
 a line_29 -1
 b line_30 -1
 c line_31 -1
 m[1,1] SOS_Row_1 1 SOS_Col_1 1
 m[1,2] SOS_Row_1 1 SOS_Col_2 1
 m[1,3] SOS_Row_1 1 SOS_Col_3 1
 m[1,4] SOS_Row_1 1 SOS_Col_4 1
 m[2,1] SOS_Row_2 1 SOS_Col_1 1
 m[2,2] SOS_Row_2 1 SOS_Col_2 1
 m[2,3] SOS_Row_2 1 SOS_Col_3 1
 m[2,4] SOS_Row_2 1 SOS_Col_4 1
 m[3,1] SOS_Row_3 1 SOS_Col_1 1
 m[3,2] SOS_Row_3 1 SOS_Col_2 1
 m[3,3] SOS_Row_3 1 SOS_Col_3 1
 m[3,4] SOS_Row_3 1 SOS_Col_4 1
 x_b[1] line_1 100.000000 x_sos[1] 1
 x_b[2] line_2 100.000000 x_sos[1] 1
 x_b[3] line_3 100.000000 x_sos[1] 1
 x_b[4] line_4 100.000000 x_sos[1] 1
 x_b[5] line_5 100.000000 x_sos[1] 1
 y_b[1] line_7 10000000000.000000 testB 1
 y_b[1] line_18 1 line_19 -1
 y_b[2] line_8 10000000000.000000 testB 1
 y_b[2] line_19 1 line_20 -1
 y_b[3] line_9 10000000000.000000 testB 1
 y_b[3] line_20 1 line_21 -1
 y_b[4] line_10 10000000000.000000 testB 1
 y_b[4] line_21 1 line_22 -1
 y_b[5] line_11 10000000000.000000 testB 1
 y_b[5] line_22 1 line_23 -1
 y_b[6] line_12 10000000000.000000 testB 1
 y_b[6] line_23 1 line_24 -1
 y_b[7] line_13 10000000000.000000 testB 1
 y_b[7] line_24 1 line_25 -1
 y_b[8] line_14 10000000000.000000 testB 1
 y_b[8] line_25 1 line_26 -1
 y_b[9] line_15 10000000000.000000 testB 1
 y_b[9] line_26 1 line_27 -1
 y_b[10] line_16 10000000000.000000 testB 1
 y_b[10] line_27 1
 y_d[1] line_18 -1 testB_sos2 1
 y_d[2] line_19 -1 testB_sos2 1
 y_d[3] line_20 -1 testB_sos2 1
 y_d[4] line_21 -1 testB_sos2 1
 y_d[5] line_22 -1 testB_sos2 1
 y_d[6] line_23 -1 testB_sos2 1
 y_d[7] line_24 -1 testB_sos2 1
 y_d[8] line_25 -1 testB_sos2 1
 y_d[9] line_26 -1 testB_sos2 1
 y_d[10] line_27 -1 testB_sos2 1
 a_b line_29 100.000000 testC 1
 b_b line_30 100.000000 testC 1
 c_b line_31 100.000000 testC 1
 GVEND 'MARKER' 'INTEND'
RHS
 RHS x_sos[1] 1 testB 2
 RHS testB_sos2 1 testC 1
 RHS SOS_Row_1 1 SOS_Row_2 1
 RHS SOS_Row_3 1 SOS_Col_1 1
 RHS SOS_Col_2 1 SOS_Col_3 1
 RHS SOS_Col_4 1
BOUNDS
 UP BOUND x[1] 100.000000
 UP BOUND x[2] 100.000000
 UP BOUND x[3] 100.000000
 UP BOUND x[4] 100.000000
 UP BOUND x[5] 100.000000
 PL BOUND y[1]
 PL BOUND y[2]
 PL BOUND y[3]
 PL BOUND y[4]
 PL BOUND y[5]
 PL BOUND y[6]
 PL BOUND y[7]
 PL BOUND y[8]
 PL BOUND y[9]
 PL BOUND y[10]
 UP BOUND a 100
 UP BOUND b 100
 UP BOUND c 100
 UP BOUND m[1,1] 1
 UP BOUND m[1,2] 1
 UP BOUND m[1,3] 1
 UP BOUND m[1,4] 1
 UP BOUND m[2,1] 1
 UP BOUND m[2,2] 1
 UP BOUND m[2,3] 1
 UP BOUND m[2,4] 1
 UP BOUND m[3,1] 1
 UP BOUND m[3,2] 1
 UP BOUND m[3,3] 1
 UP BOUND m[3,4] 1
 UP BOUND x_b[1] 1
 UP BOUND x_b[2] 1
 UP BOUND x_b[3] 1
 UP BOUND x_b[4] 1
 UP BOUND x_b[5] 1
 UP BOUND y_b[1] 1
 UP BOUND y_b[2] 1
 UP BOUND y_b[3] 1
 UP BOUND y_b[4] 1
 UP BOUND y_b[5] 1
 UP BOUND y_b[6] 1
 UP BOUND y_b[7] 1
 UP BOUND y_b[8] 1
 UP BOUND y_b[9] 1
 UP BOUND y_b[10] 1
 UP BOUND y_d[1] 1
 UP BOUND y_d[2] 1
 UP BOUND y_d[3] 1
 UP BOUND y_d[4] 1
 UP BOUND y_d[5] 1
 UP BOUND y_d[6] 1
 UP BOUND y_d[7] 1
 UP BOUND y_d[8] 1
 UP BOUND y_d[9] 1
 UP BOUND y_d[10] 1
 UP BOUND a_b 1
 UP BOUND b_b 1
 UP BOUND c_b 1
ENDATA
