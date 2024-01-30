<?php

$num = 10;
$arr[] = 1;
$arr[] = 2;
$str = "string value";

echo "BEFORE FUNCTION\n";
echo $num . "\n";
echo "array: \n";
echo $arr[0] . "\n" . $arr[1] . "\n";
echo "string: \n";
echo $str . "\n";

function shift($num, $arr, $str) {
    $num = 5;
    $arr[0] = 3;
    $arr[1] = 4;
    $str = "other string";
    echo "IN FUNCTION AFTER CHANGES\n";
	echo $num . "\n";
    echo "array: \n";
    echo $arr[0] . "\n" . $arr[1] . "\n";
    echo "string: \n";
    echo $str . "\n";
}

shift($num, $arr, $str);

echo "AFTER FUNCTION\n";
echo $num . "\n";
echo "array: \n";
echo $arr[0] . "\n" . $arr[1] . "\n";
echo "string: \n";
echo $str . "\n";
