use std::fs::File;
use std::io::{self, prelude::*, BufReader};
use std::collections::HashSet;

type Pos = (i32, i32);

fn main() -> io::Result<()> {
    let file = File::open("input.txt")?;
    let reader = BufReader::new(file);

    // Create array to store multiple knots and initialize it with the starting positions
    let mut knots: Vec<Pos> = vec![((0, 0)); 10];

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
                if let Some(newPos) = move_knot(&knots[i - 1], &knots[i]) {
                    knots[i] = newPos;
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

fn move_knot(head: &Pos, tail: &Pos) -> Option<Pos> {
    let (diffX, diffY) = (tail.0 - head.0, tail.1 - head.1);
    let (diffX1, diffY1) = (diffX.clamp(-1, 1), diffY.clamp(-1, 1));

    return match (diffX.abs() == 2, diffY.abs() == 2) {
        // If difference in x and y is 2, move both x and y
        (true, true) => Some((head.0 + diffX1, head.1 + diffY1)),
        // If difference in x is 2 then move the tail in the correct x direction
        (true, false) => Some((head.0 + diffX1, head.1)),
        // If the difference in y is 2 then move the tail in the correct y direction
        (false, true) => Some((head.0, head.1 + diffY1)),
        // Don't move
        _ => None,
    };
}