<?php

//Заполняем нулями

$arr_vect[] = 0;
$arr_vect[] = 0;
$arr_vect[] = 0;
$arr_vect[] = 0;
$arr_vect[] = 0;
$arr_vect[] = 1; //
$arr_vect[] = 0;
$arr_vect[] = 0;
$arr_vect[] = 0;
$arr_vect[] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 0;
$arr_vect[4] = 0;
$arr_vect[5] = 1; //
$arr_vect[6] = 0;
$arr_vect[7] = 0;
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 0;
$arr_vect[4] = 1; //
$arr_vect[5] = 0;
$arr_vect[6] = 0;
$arr_vect[7] = 0;
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 1; //
$arr_vect[4] = 0;
$arr_vect[5] = 0;
$arr_vect[6] = 0;
$arr_vect[7] = 0;
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 1; //
$arr_vect[4] = 0;
$arr_vect[5] = 0;
$arr_vect[6] = 0;
$arr_vect[7] = 0;
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 0;
$arr_vect[4] = 1; //
$arr_vect[5] = 0;
$arr_vect[6] = 0;
$arr_vect[7] = 0;
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 0;
$arr_vect[4] = 0;
$arr_vect[5] = 1; //
$arr_vect[6] = 0;
$arr_vect[7] = 0;
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 0;
$arr_vect[4] = 0;
$arr_vect[5] = 0;
$arr_vect[6] = 1; //
$arr_vect[7] = 0;
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 0;
$arr_vect[4] = 0;
$arr_vect[5] = 0;
$arr_vect[6] = 0;
$arr_vect[7] = 1; //
$arr_vect[8] = 0;
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

$arr_vect[0] = 0;
$arr_vect[1] = 0;
$arr_vect[2] = 0;
$arr_vect[3] = 0;
$arr_vect[4] = 0;
$arr_vect[5] = 0;
$arr_vect[6] = 0;
$arr_vect[7] = 0;
$arr_vect[8] = 1; //
$arr_vect[9] = 0;

$arr_matr[] = $arr_vect;

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