<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <div class=".<\?php>">
        <?php if ($_COOKIE): $a = 1; $b = 2?>
        <?php else: ?>
        <? echo "SOMETHING \$";?>
        <?php echo "abc
                    cbd";?>
        <!-- <\?php -->
        <?php endif?>
        <?php for ($i = 0; $i <= 1; $i = $i+1):?>
        <?php endfor;?>
        <?php while (1): ?>
            <?php break; endwhile;?>
        <?php switch(true):
                case 1: ?>
            <?php case 2: ?>
            <?php default:?>
        <?php endswitch;?>
    </div>
</body>
</html>

<?php
// Example class 

$b = ( fLoat ) 100;

//function b () {}

// Creating instances of the Person class
$str = '\n \\ \'';
$nul = (int) 1;

('a' . 's')[0];

static $int = 1_000;
// $hexdec = 0x1A;
// $octal = 0123;
// $octal_other = 0o123;
// $binary = 0b11111111;
// $interpolStr = "String interpol $int"; //Unsupported
$interpolStrOther = "String interpol {$person->name}"; //TODO Ошибка на этом моменте;

// Loops - for loop
for ($i = 0; $i < count($persons); $i=$i+1) {
//     $persons[$i]->greet();
}

// foreach (($persons) as $ke => &$a) {
//     # code...
//     PHP_EOL;
// }
//
// // Loops - do-while loop
// $k = 0;
// do {
//     $persons[$k]->greet();
//     $k=$k+1;
// } while ($k < count($persons));


// $rev = &$val;