<?php
$arr[] = 5;
$arr[] = 3;
$arr[] = 1;
$arr[] = 2;
$arr[] = 4;

for ($i = 0; $i < 4; $i=$i+1) {
    for ($j = 0; $j < 4; $j=$j+1) {
        if ($arr[$j] > $arr[$j + 1]) {
            $tmp = $arr[$j];
            $arr[$j] = $arr[$j + 1];
            $arr[$j + 1] = $tmp;
        }
    }
}

for ($i = 0; $i < 5; $i=$i+1) {
    echo $arr[$i];
    echo "\n";
}
