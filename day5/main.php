<?php
// Read file line by line
$handle = fopen("input.txt", "r");

$stackLines = [];

// Read lines until we hit an empty line
while (($line = fgets($handle)) !== false) {
    if (trim($line) == "") {
        break;
    }
    array_push($stackLines, $line);
}

// Get list of stack ids in order they appear in the input
$stackIds = explode(" ", preg_replace('/\s+/', ' ', trim(array_pop($stackLines))));

// Create dictionary of stacks
$stacks = [];
foreach ($stackIds as $id) {
    $stacks[$id] = [];
}

// Populate stacks with values
// Reverse loop through lines that make up the stack
for (end($stackLines); key($stackLines)!==null; prev($stackLines)){
    $currentElement = current($stackLines);

    // Every 4th character is a space. Everything inbetween is either spaces or a character that
    // should be added to the appropriate stack

    for ($i = 1; $i <= strlen($currentElement) - 4; $i+=4) {
        $currentChar = $currentElement[$i];

        if (trim($currentChar) != "") {
            $stackId = $stackIds[($i-1)/4];
            array_push($stacks[$stackId], $currentChar);
        }
    }
}

// Create copy of stacks
$stacksCopy = [];
foreach ($stacks as $id => $stack) {
    $stacksCopy[$id] = array_merge([], $stack);
}

// Read remaining lines. These are the commands
while (($line = fgets($handle)) !== false) {
    // Remove newline
    $line = trim($line);

    // Remove "move from to" from the line
    $line = str_replace("move ", "", $line);
    $line = str_replace("from ", "", $line);
    $line = str_replace("to ", "", $line);

    // Split the line into 3 parts
    $parts = explode(" ", $line);

    // Get the amount, from and to
    $amount = $parts[0];
    $from = $parts[1];
    $to = $parts[2];

    // Move the characters to solve part 1
    for ($i = 0; $i < $amount; $i++) {
        $char = array_pop($stacks[$from]);
        array_push($stacks[$to], $char);
    }

    // Move the characters to solve part 2

    # Remove the characters from the from stack
    $slice = array_splice($stacksCopy[$from], -$amount);
    # Add the characters to the to stack in the same order (add slice to end of array)
    $stacksCopy[$to] = array_merge($stacksCopy[$to], $slice);
}

# Done reading file
fclose($handle);

echo("Part 1: ");
// Print top of each stack
foreach ($stacks as $id => $stack) {
    echo array_pop($stack);
}
echo("\n");

echo("Part 2: ");
foreach ($stacksCopy as $id => $stack) {
    echo array_pop($stack);
}
echo("\n");

?>