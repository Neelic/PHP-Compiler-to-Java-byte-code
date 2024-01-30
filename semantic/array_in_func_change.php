<?php
$a = array(1,2,3,4);

for ($i = 0; $i < sizeof($a); $i++){
	echo ($a[$i]);	
}

$b = readline();

echo ($a[$b]);

function shift() {
	$a[$b] = 10;
}

for ($i = 0; $i < sizeof($a); $i++){
	echo ($a[$i]);	
}