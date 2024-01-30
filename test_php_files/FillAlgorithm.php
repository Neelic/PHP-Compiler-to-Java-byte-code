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

function _fill(&$arr_to_fill, $x, $y){
	
	if($arr_to_fill[$x][$y] == 1 || $arr_to_fill[$x][$y] == 2) return;
	
	$arr_to_fill[$x][$y] = 2;
	
	if($x + 1  < 10){
		_fill($arr_to_fill, $x+1, $y);
	}
	if($x > 0){
		_fill($arr_to_fill, $x-1, $y);
	}
	if($y + 1  < 10){
		_fill($arr_to_fill, $x, $y+1);
	}
	if($y > 0){
		_fill($arr_to_fill, $x, $y-1);
	}
	
}

_fill($arr_matr, 2,2);

$res = "";

for ($i = 0; $i < 10; $i++){
	for ($j = 0; $j<10; $j++){
		$res .= $arr_matr[$i][$j];
	}
	
	$res .= "\n";
}

echo $res;