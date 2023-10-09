<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <div class=".<\?php>">
        <? echo "SOMETHING \$" ?>
        <!-- <\?php -->
    </div>
</body>
</html>

<?php
// Example class
class Person
{
    public $name;
    private static $age;

    public function __construct($name, $age)
    {
        $this->name = $name;
        $this->age = $age;
    }

    public function greet()
    {
        echo "Hello, my name is " . $this->name . " and I am " . self::$age . " years old." . PHP_EOL;
        die();
    }

    public static function statFunc()
    {
        echo "Hello, my name is A and I am " . self::$age . " years \t old." . PHP_EOL;
    }
}

// Creating instances of the Person class
$person1 = new Person("John", 2.5);
$person2 = new Person("Jane", 30);
$str = '\s';

Person::statFunc();

$persons = [$person1, $person2];

$int = 1_000; 
$hexdec = 0x1A;
$octal = 0123;
$octal_other = 0o123;
$binary = 0b11111111;
$interpolStr = "String interpol $int";
$interpolStrOther = "String interpol {$person->name}";

// Loops - for loop
for ($i = 0; $i < count($persons); $i++) {
    $persons[$i]->greet();
}

// Loops - while loop
$j = 0;
while ($j < count($persons)) {
    $persons[$j]->greet();
    $j++;
}

// Loops - do-while loop
$k = 0;
do {
    $persons[$k]->greet();
    $k++;
} while ($k < count($persons));

// Conditionals - if-else statement
$age = 40;
if ($age > 30) {
    echo "You are over $age years old." . PHP_EOL;
} else {
    echo "You are under {$age} years old." . PHP_EOL;
}
/*
gnjrgvnrvnvrnrvnrin
vasl*feiii$ddwdw=mrmvir)(){}
*/

// Conditionals - switch statement
$day = "Monday";
switch ($day) {
    case "Monday":
        echo "Today is Monday." . PHP_EOL;
        break;
    case "Tuesday":
        echo "Today is Tuesday." . PHP_EOL;
        break;
    default:
        echo "Today is not Monday or Tuesday." . PHP_EOL;
        break;
}

// Conditionals - match (added in PHP 8.0)
$number = 2;
$matchResult = match ($number) {
    1 => "One",
    2 => "Two",
    default => "Other",
};
echo "Match result: " . $matchResult . PHP_EOL;

$float_lin = 1_234.567;
$float_exp = 1.2e3;
$float_exp_alt = 7E-10;
$float_lin_exp = 1_23.45e-2_0;
$somenullby = 0;

declare(ticks=1);

goto a;

a:
echo 'Bar';

$output = `ls -al`;

$rev = &$val;