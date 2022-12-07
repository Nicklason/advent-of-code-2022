const fs = require('fs');

const data = fs.readFileSync('./input.txt', 'utf8');

const lines = data.split('\n');

let highest = 0;
let current = 0;

for (let i = 0; i < lines.length; i++) {
    const line = lines[i];

    if (line === '') {
        if (current > highest) {
            highest = current;
        }

        current = 0;
        continue;
    }

    const calories = parseInt(line, 10);

    current += calories;
}

console.log(highest);
