<?php
$arr_vect[] = 0;
$arr_matr[] = $arr_vect;

for ($i = 0; $i < 10; $i = $i + 1){
	for ($j = 0; $j<10; $j = $j + 1){
		if($j == 5 ){
			$arr_vect[$j] = 1;
		} else {
			$arr_vect[$j] = 0;
		}
		
	}
	$arr_matr[$i] = $arr_vect;
}

function _fill($arr_to_fill, $x, $y){
	
	if($arr_to_fill[$x][$y] == 1 || $arr_to_fill[$x][$y] == 2) return;
	
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

	return $arr_to_fill;
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