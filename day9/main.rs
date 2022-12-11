use std::fs::File;
use std::io::{self, prelude::*, BufReader};
use std::collections::HashSet;

fn main() -> io::Result<()> {
    let file = File::open("input.txt")?;
    let reader = BufReader::new(file);

    let mut tailVisitedPositions = HashSet::new();
    let mut headX: i32 = 0;
    let mut headY: i32 = 0;
    let mut tailX = headX;
    let mut tailY = headY;

    // Add start position to set
    tailVisitedPositions.insert((tailX, tailY));

    // Read each line of the file and move the head and tail accordingly
    for line in reader.lines() {
        let line = line?;

        // Get direction and steps from line
        let direction = line.chars().nth(0).unwrap();
        let steps = &line[2..].parse::<i32>().unwrap();

        // Loop through each steps
        let mut i: i32 = -1;
        while i < steps - 1 {
            i += 1;

            // Move head in direction
            match direction {
                'U' => headY += 1,
                'D' => headY -= 1,
                'L' => headX -= 1,
                'R' => headX += 1,
                _ => println!("Unknown direction")
            }

            let diffX = (headX - tailX).abs();
            let diffY = (headY - tailY).abs();

            // If head and tail are 3 apart then move the tail in both the x and y direction
            if diffX + diffY == 3 {
                if headX > tailX {
                    tailX += 1;
                } else {
                    tailX -= 1;
                }

                if headY > tailY {
                    tailY += 1;
                } else {
                    tailY -= 1;
                }
            // If difference in x is greater than 1 then move the tail in the correct x direction
            } else if diffX > 1 {
                if headX > tailX {
                    tailX += 1;
                } else {
                    tailX -= 1;
                }
            // If the difference in y is greater than 1 then move the tail in the correct y direction
            } else if diffY > 1 {
                if headY > tailY {
                    tailY += 1;
                } else {
                    tailY -= 1;
                }
            }

            // Add tail position to set
            tailVisitedPositions.insert((tailX, tailY));
        }
    }

    println!("{}", tailVisitedPositions.len());

    Ok(())
}
