<?php

//Заполняем нулями

$arr_matr[0][0] = 0;
$arr_matr[0][1] = 0;
$arr_matr[0][2] = 0;
$arr_matr[0][3] = 0;
$arr_matr[0][4] = 0;
$arr_matr[0][5] = 1; //
$arr_matr[0][6] = 0;
$arr_matr[0][7] = 0;
$arr_matr[0][8] = 0;
$arr_matr[0][9] = 0;

$arr_matr[1][0] = 0;
$arr_matr[1][1] = 0;
$arr_matr[1][2] = 0;
$arr_matr[1][3] = 0;
$arr_matr[1][4] = 0;
$arr_matr[1][5] = 1; //
$arr_matr[1][6] = 0;
$arr_matr[1][7] = 0;
$arr_matr[1][8] = 0;
$arr_matr[1][9] = 0;

$arr_matr[2][0] = 0;
$arr_matr[2][1] = 0;
$arr_matr[2][2] = 0;
$arr_matr[2][3] = 0;
$arr_matr[2][4] = 1; //
$arr_matr[2][5] = 0;
$arr_matr[2][6] = 0;
$arr_matr[2][7] = 0;
$arr_matr[2][8] = 0;
$arr_matr[2][9] = 0;

$arr_matr[3][0] = 0;
$arr_matr[3][1] = 0;
$arr_matr[3][2] = 0;
$arr_matr[3][3] = 1; //
$arr_matr[3][4] = 0;
$arr_matr[3][5] = 0;
$arr_matr[3][6] = 0;
$arr_matr[3][7] = 0;
$arr_matr[3][8] = 0;
$arr_matr[3][9] = 0;

$arr_matr[4][0] = 0;
$arr_matr[4][1] = 0;
$arr_matr[4][2] = 0;
$arr_matr[4][3] = 1; //
$arr_matr[4][4] = 0;
$arr_matr[4][5] = 0;
$arr_matr[4][6] = 0;
$arr_matr[4][7] = 0;
$arr_matr[4][8] = 0;
$arr_matr[4][9] = 0;

$arr_matr[5][0] = 0;
$arr_matr[5][1] = 0;
$arr_matr[5][2] = 0;
$arr_matr[5][3] = 0;
$arr_matr[5][4] = 1; //
$arr_matr[5][5] = 0;
$arr_matr[5][6] = 0;
$arr_matr[5][7] = 0;
$arr_matr[5][8] = 0;
$arr_matr[5][9] = 0;

$arr_matr[6][0] = 0;
$arr_matr[6][1] = 0;
$arr_matr[6][2] = 0;
$arr_matr[6][3] = 0;
$arr_matr[6][4] = 0;
$arr_matr[6][5] = 1; //
$arr_matr[6][6] = 0;
$arr_matr[6][7] = 0;
$arr_matr[6][8] = 0;
$arr_matr[6][9] = 0;

$arr_matr[7][0] = 0;
$arr_matr[7][1] = 0;
$arr_matr[7][2] = 0;
$arr_matr[7][3] = 0;
$arr_matr[7][4] = 0;
$arr_matr[7][5] = 0;
$arr_matr[7][6] = 1; //
$arr_matr[7][7] = 0;
$arr_matr[7][8] = 0;
$arr_matr[7][9] = 0;

$arr_matr[8][0] = 0;
$arr_matr[8][1] = 0;
$arr_matr[8][2] = 0;
$arr_matr[8][3] = 0;
$arr_matr[8][4] = 0;
$arr_matr[8][5] = 0;
$arr_matr[8][6] = 0;
$arr_matr[8][7] = 1; //
$arr_matr[8][8] = 0;
$arr_matr[8][9] = 0;

$arr_matr[9][0] = 0;
$arr_matr[9][1] = 0;
$arr_matr[9][2] = 0;
$arr_matr[9][3] = 0;
$arr_matr[9][4] = 0;
$arr_matr[9][5] = 0;
$arr_matr[9][6] = 0;
$arr_matr[9][7] = 0;
$arr_matr[9][8] = 1; //
$arr_matr[9][9] = 0;

/*
0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 1 0
*/



function _fill($arr_to_fill, $x, $y){
	
	if($arr_to_fill[$x][$y] == 0){
        $arr_to_fill[$x][$y] = 2;

            if($x + 1  < 10){
                $arr_to_fill = _fill($arr_to_fill, $x+1, $y);
            }
            if($x > 0){
                $arr_to_fill = _fill($arr_to_fill, $x-1, $y);
            }
            if($y + 1  < 10){
                $arr_to_fill = _fill($arr_to_fill, $x, $y+1);
            }
            if($y > 0){
                $arr_to_fill = _fill($arr_to_fill, $x, $y-1);
            }
	}
	


	return $arr_to_fill;
}

$res = "";

for ($i = 0; $i < 10; $i = $i + 1){
	for ($j = 0; $j<10; $j = $j + 1){
		$res = $res . $arr_matr[$i][$j];
	}
	
	$res = $res . "\n";
}

$arr_matr = _fill($arr_matr, 2,2);

$res = "";

for ($i = 0; $i < 10; $i = $i + 1){
	for ($j = 0; $j<10; $j = $j + 1){
		$res = $res . $arr_matr[$i][$j];
	}
	
	$res = $res . "\n";
}

echo $res;