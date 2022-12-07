# Rock, paper, scissors
opponentShape = ["A", "B", "C"]
playerShape = ["X", "Y", "Z"]
shapeScore = [1, 2, 3]
# Lose, draw, win
outcomeScore = [0, 3, 6]

# rock (0) beats scissors (2)
# scissors (2) beats paper (1)
# paper (1) beats rock (0)

# R R = 0 (draw)
# R P = -1 (lose)
# R S = -2 (win)
# P R = 1 (win)
# P P = 0 (draw)
# P S = -1 (lose)
# S R = 2 (lose)
# S P = 1 (win)
# S S = 0 (draw)

# -2 = win
# -1 = lose
# 0 = draw
# 1 = win
# 2 = lose

score = 0

with open("input.txt", "r") as f:
    for line in f:
        opponent = line[0]
        player = line[2]

        opponentIndex = opponentShape.index(opponent)
        playerIndex = playerShape.index(player)

        difference = playerIndex - opponentIndex

        if difference == 0:
            # Draw
            score += outcomeScore[1]
        elif difference == 1 or difference == -2:
            # Player wins
            score += outcomeScore[2]
        else:
            # Player loses
            score += outcomeScore[0]
        
        # Add shape score
        score += shapeScore[playerIndex]

print(score)
