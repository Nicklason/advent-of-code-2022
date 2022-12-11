use std::fs::File;
use std::io::{self, prelude::*, BufReader};
use std::collections::HashSet;

fn main() -> io::Result<()> {
    let file = File::open("input.txt")?;
    let reader = BufReader::new(file);

    // Create array to store multiple knots
    let mut knots: Vec<(i32, i32)> = Vec::new();

    // Create 10 knots and add to array
    for _ in 0..10 {
        knots.push((0,0));
    }

    let mut tailVisitedPositions = HashSet::new();
    let mut secondKnotVisitedPositions = HashSet::new();

    // Read each line of the file and move the head and tail accordingly
    for line in reader.lines() {
        let line = line?;

        // Get direction and steps from line

        let (x, y, steps) = match line.split_at(2) {
            ("U ", n) => (0, 1, n),
            ("D ", n) => (0, -1, n),
            ("L ", n) => (-1, 0, n),
            ("R ", n) => (1, 0, n),
            _ => unreachable!()
        };

        // Loop through each step
        for _ in 0..steps.parse::<i32>().unwrap() {
            // Move head in direction
            knots[0].0 += x;
            knots[0].1 += y;

            // Loop through each knot
            for i in 1..knots.len() {
                let diffX = (knots[i - 1].0 - knots[i].0).abs();
                let diffY = (knots[i - 1].1 - knots[i].1).abs();

                // If head and tail are 3 or more apart then move the tail in both the x and y direction
                if diffX + diffY >= 3 {
                    knots[i].0 += if knots[i - 1].0 > knots[i].0 { 1 } else { -1 };
                    knots[i].1 += if knots[i - 1].1 > knots[i].1 { 1 } else { -1 };
                // If difference in x is greater than 1 then move the tail in the correct x direction
                } else if diffX == 2 {
                    knots[i].0 += if knots[i - 1].0 > knots[i].0 { 1 } else { -1 };
                // If the difference in y is greater than 1 then move the tail in the correct y direction
                } else if diffY == 2 {
                    knots[i].1 += if knots[i - 1].1 > knots[i].1 { 1 } else { -1 };
                } else {
                    break;
                }
            }

            // Add tail position to set
            secondKnotVisitedPositions.insert(knots[1]);
            tailVisitedPositions.insert(knots[9]);
        }
    }

    println!("Part 1: {}", secondKnotVisitedPositions.len());

    println!("Part 2: {}", tailVisitedPositions.len());

    Ok(())
}
