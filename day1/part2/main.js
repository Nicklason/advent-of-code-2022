const fs = require('fs');

const data = fs.readFileSync('./input.txt', 'utf8');

const lines = data.split('\n');

const elves = [];

let current = 0;

for (let i = 0; i < lines.length; i++) {
    const line = lines[i];

    if (line === '') {
        elves.push(current);
        current = 0;
        continue;
    }

    const calories = parseInt(line, 10);

    current += calories;
}

const sumTopThree = elves.sort((a, b) => a - b).slice(-3).reduce((a, b) => a + b)

console.log(sumTopThree);
