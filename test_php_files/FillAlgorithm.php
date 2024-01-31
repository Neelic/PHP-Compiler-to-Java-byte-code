<?php
$arr_vect[] = 0;
$arr_matr[] = $arr_vect;


//Заполняем нулями

$arr_vect[0][0] = 0;
$arr_vect[0][1] = 0;
$arr_vect[0][2] = 0;
$arr_vect[0][3] = 0;
$arr_vect[0][4] = 0;
$arr_vect[0][5] = 1; //
$arr_vect[0][6] = 0;
$arr_vect[0][7] = 0;
$arr_vect[0][8] = 0;
$arr_vect[0][9] = 0;

$arr_vect[1][0] = 0;
$arr_vect[1][1] = 0;
$arr_vect[1][2] = 0;
$arr_vect[1][3] = 0;
$arr_vect[1][4] = 0;
$arr_vect[1][5] = 1; //
$arr_vect[1][6] = 0;
$arr_vect[1][7] = 0;
$arr_vect[1][8] = 0;
$arr_vect[1][9] = 0;

$arr_vect[2][0] = 0;
$arr_vect[2][1] = 0;
$arr_vect[2][2] = 0;
$arr_vect[2][3] = 0;
$arr_vect[2][4] = 1; //
$arr_vect[2][5] = 0;
$arr_vect[2][6] = 0;
$arr_vect[2][7] = 0;
$arr_vect[2][8] = 0;
$arr_vect[2][9] = 0;

$arr_vect[3][0] = 0;
$arr_vect[3][1] = 0;
$arr_vect[3][2] = 0;
$arr_vect[3][3] = 1; //
$arr_vect[3][4] = 0;
$arr_vect[3][5] = 0;
$arr_vect[3][6] = 0;
$arr_vect[3][7] = 0;
$arr_vect[3][8] = 0;
$arr_vect[3][9] = 0;

$arr_vect[4][0] = 0;
$arr_vect[4][1] = 0;
$arr_vect[4][2] = 0;
$arr_vect[4][3] = 1; //
$arr_vect[4][4] = 0;
$arr_vect[4][5] = 0;
$arr_vect[4][6] = 0;
$arr_vect[4][7] = 0;
$arr_vect[4][8] = 0;
$arr_vect[4][9] = 0;

$arr_vect[5][0] = 0;
$arr_vect[5][1] = 0;
$arr_vect[5][2] = 0;
$arr_vect[5][3] = 0;
$arr_vect[5][4] = 1; //
$arr_vect[5][5] = 0;
$arr_vect[5][6] = 0;
$arr_vect[5][7] = 0;
$arr_vect[5][8] = 0;
$arr_vect[5][9] = 0;

$arr_vect[6][0] = 0;
$arr_vect[6][1] = 0;
$arr_vect[6][2] = 0;
$arr_vect[6][3] = 0;
$arr_vect[6][4] = 0;
$arr_vect[6][5] = 1; //
$arr_vect[6][6] = 0;
$arr_vect[6][7] = 0;
$arr_vect[6][8] = 0;
$arr_vect[6][9] = 0;

$arr_vect[7][0] = 0;
$arr_vect[7][1] = 0;
$arr_vect[7][2] = 0;
$arr_vect[7][3] = 0;
$arr_vect[7][4] = 0;
$arr_vect[7][5] = 0;
$arr_vect[7][6] = 1; //
$arr_vect[7][7] = 0;
$arr_vect[7][8] = 0;
$arr_vect[7][9] = 0;

$arr_vect[8][0] = 0;
$arr_vect[8][1] = 0;
$arr_vect[8][2] = 0;
$arr_vect[8][3] = 0;
$arr_vect[8][4] = 0;
$arr_vect[8][5] = 0;
$arr_vect[8][6] = 0;
$arr_vect[8][7] = 1; //
$arr_vect[8][8] = 0;
$arr_vect[8][9] = 0;

$arr_vect[9][0] = 0;
$arr_vect[9][1] = 0;
$arr_vect[9][2] = 0;
$arr_vect[9][3] = 0;
$arr_vect[9][4] = 0;
$arr_vect[9][5] = 0;
$arr_vect[9][6] = 0;
$arr_vect[9][7] = 0;
$arr_vect[9][8] = 1; //
$arr_vect[9][9] = 0;

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