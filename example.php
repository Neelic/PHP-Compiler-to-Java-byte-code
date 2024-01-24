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

class Person
{
    static public $name = 100;
    private static $age;

    public function __construct($name, $age)
    {
        $this->name = $name;
    }

    public function greet()
    {
        echo "Hello, \u{41} my \x41 name is " . $this->name . " and I am " . self::age . " years old." . PHP_EOL;
    }

    public static function statFunc($name)
    {
        echo "Hello,\ \ \my $name \is A \n \x and I am " . self::age . " years old." . PHP_EOL;
    }
}

abstract class Example extends Person {
    //use property, ai; error
    abstract public $c = 1;
    private const NAME = 1, abc = '123';
    protected function b() {
        parent::greet();
    }
    public abstract static function a();
}

interface objectO {}

interface interfaceO extends objectO {
    public function a($a = 1);
}

trait TraitName {
    public abstract static $a = 1;
    protected abstract function r();
}
$b = ( fLoat ) 100;

function b () {}

b()::a;

// Creating instances of the Person class
$person1 = new Person("John", 2.5);
$person2 = new Person("Jane", 30);
echo $person1::name[0];
$str = '\n \\ \'';
$nul = (int) 1;

Person::statFunc('a');

('a' . 's')[0];

static $int = 1_000;
// $hexdec = 0x1A;
// $octal = 0123;
// $octal_other = 0o123;
// $binary = 0b11111111;
$interpolStr = "String interpol $int";
$interpolStrOther = "String interpol {$person->name}"; //TODO Ошибка на этом моменте;

// Loops - for loop
for ($i = 0; $i < count($persons); $i=$i+1) {
    $persons[$i]->greet();
}

foreach (($persons) as $ke => &$a) {
    # code...
    PHP_EOL;
}

// Loops - do-while loop
$k = 0;
do {
    $persons[$k]->greet();
    $k=$k+1;
} while ($k < count($persons));


$rev = &$val;