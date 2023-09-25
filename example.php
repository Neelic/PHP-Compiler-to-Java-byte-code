<?
// Example class
class Person
{
    private $name;
    private $age;

    public function __construct($name, $age)
    {
        $this->name = $name;
        $this->age = $age;
    }

    public function greet()
    {
        echo "Hello, my name is " . $this->name . " and I am " . $this->age . " years old." . PHP_EOL;
    }
}

// Creating instances of the Person class
$person1 = new Person("John", 25);
$person2 = new Person("Jane", 30);

$persons = [$person1, $person2];

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
    echo "You are over 30 years old." . PHP_EOL;
} else {
    echo "You are under 30 years old." . PHP_EOL;
}

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
