<?php

$arr_vect[] = 0;
$arr_matr[] = $arr_vect;

for ($i = 0; $i < 10; $i = $i + 1){
	for ($j = 0; $j<10; $j = $j +1){
		if($j == 5 ){
			$arr_vect[$j] = 1;
		} else {
			$arr_vect[$j] = 0;
		}
		
	}
	$arr_matr[$i] = $arr_vect;
}

$res = "";

for ($i = 0; $i < 10; $i = $i + 1){
	for ($j = 0; $j<10; $j = $j + 1){
		$res = $res . $arr_matr[$i][$j];
	}
	
	$res = $res . "\n";
}

echo $res;