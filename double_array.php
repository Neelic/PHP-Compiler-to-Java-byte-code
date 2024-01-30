<?php

$arr_vect[] = 0;
$arr_matr[] = $arr_vect;

for ($i = 0; $i < 10; $i++){
	for ($j = 0; $j<10; $j++){
		if($j == 5 ){
			$arr_vect[$j] = 1;
		} else {
			$arr_vect[$j] = 0;
		}
		
	}
	$arr_matr[$i] = $arr_vect;
}

$res = "";

for ($i = 0; $i < 10; $i++){
	for ($j = 0; $j<10; $j++){
		$res .= $arr_matr[$i][$j];
	}
	
	$res .= "\n";
}

echo $res;