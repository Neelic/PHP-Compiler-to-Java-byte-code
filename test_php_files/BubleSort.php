<?php
$count = (int) readline();
for ($v = 0; $v < $count; $v = $v + 1) {
    $arr[] = (int) readline();
}

for ($i = 0; $i < $count - 1; $i=$i+1) {
    for ($j = 0; $j < $count - 1; $j=$j+1) {
        if ($arr[$j] > $arr[$j + 1]) {
            $tmp = $arr[$j];
            $arr[$j] = $arr[$j + 1];
            $arr[$j + 1] = $tmp;
        }
    }
}

echo "Сортированный массив\n";
for ($i = 0; $i < $count; $i=$i+1) {
    echo $arr[$i];
    echo "\n";
}
