#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::vector<std::vector<int>> createMatrix(int, int);
void populateMatrix(std::vector<std::vector<int>> &);
std::vector<int> getRow(std::vector<std::vector<int>>, int);
std::vector<int> getColumn(std::vector<std::vector<int>>, int);
bool isVisibleInRow(std::vector<int>, int);
int getVisibleTreesOnLeft(std::vector<int>, int);
int getScore(std::vector<std::vector<int>>, int, int);

int main()
{
  int rows = 99;
  int columns = 99;

  auto vec = createMatrix(rows, columns);

  // Populate the matrix
  populateMatrix(vec);

  // All outside trees can be seen
  int visible = rows * 2 + (columns - 2) * 2;

  int highestScore = 0;

  // Loop through all inner trees and check if they can be seen
  for (int i = 1; i < vec.size() - 1; i++)
  {
    for (int j = 1; j < vec[i].size() - 1; j++)
    {
      auto row = getRow(vec, i);
      auto column = getColumn(vec, j);

      // Check if tree is visible from any direction
      if (isVisibleInRow(row, j) || isVisibleInRow(column, i))
      {
        visible++;
      }

      // Get the number of trees visible from each direction

      // Get trees visible on left using row and column index
      int treesVisibleLeft = getVisibleTreesOnLeft(row, j);
      // Get trees visible on right by reversing the row and index
      int treesVisibleRight = getVisibleTreesOnLeft(std::vector<int>(row.rbegin(), row.rend()), row.size() - j - 1);
      // Get trees visible on top using column and row index
      int treesVisibleTop = getVisibleTreesOnLeft(column, i);
      // Get trees visible on bottom by reversing the column and index
      int treesVisibleBottom = getVisibleTreesOnLeft(std::vector<int>(column.rbegin(), column.rend()), column.size() - i - 1);

      int score = treesVisibleLeft * treesVisibleRight * treesVisibleTop * treesVisibleBottom;
      if (score > highestScore)
      {
        highestScore = score;
      }
    }
  }

  std::cout << "Part 1: " << visible << std::endl;
  std::cout << "Part 2: " << highestScore << std::endl;

  return 0;
}

std::vector<std::vector<int>> createMatrix(int row, int column)
{
  std::vector<std::vector<int>> vec(row);

  for (int i = 0; i < row; i++)
  {
    vec[i] = std::vector<int>(column);
    for (int j = 0; j < column; j++)
    {
      vec[i][j] = 0;
    }
  }

  return vec;
}

void populateMatrix(std::vector<std::vector<int>> &vec)
{
  // Create read stream
  std::ifstream input("input.txt");

  std::string line;

  int lineIndex = 0;
  // Read line by line
  while (std::getline(input, line))
  {
    for (int i = 0; i < line.length(); i++)
    {
      vec[lineIndex][i] = (int)line[i] - 48;
    }

    // Add the line to the map
    lineIndex++;
  }

  // Close the file
  input.close();
}

std::vector<int> getRow(std::vector<std::vector<int>> vec, int row)
{
  // Create a copy of the row vector
  std::vector<int> rowVec(vec.size());
  rowVec = vec[row];
  return rowVec;
}

std::vector<int> getColumn(std::vector<std::vector<int>> vec, int column)
{
  std::vector<int> columnVec(vec.size());

  for (int i = 0; i < vec.size(); i++)
  {
    columnVec[i] = vec[i][column];
  }

  return columnVec;
}

int getVisibleTreesOnLeft(std::vector<int> vec, int index)
{
  int distance = 0;

  // Loop from right to left
  // Check if tree is visible from right
  for (int i = index - 1; i >= 0; i--)
  {
    distance++;
    if (vec[i] >= vec[index])
    {
      break;
    }
  }

  return distance;
}

bool isVisibleInRow(std::vector<int> vec, int index)
{
  int tallest = vec[0];

  bool isVisible = false;

  // Loop through row from left to right

  for (int i = 1; i < vec.size(); i++)
  {
    // Check if we reached the current tree
    if (i == index)
    {
      // Check if tree is visible from left
      if (vec[i] > tallest)
      {
        // Tree is visible, so we can skip the rest of the trees in the row
        return true;
      }

      // Tree is not visible, reset tallest and continue to check from the right
      tallest = 0;
      continue;
    }

    // Check if tree is taller than the current tallest tree
    if (vec[i] > tallest)
    {
      tallest = vec[i];
    }
  }

  // If we reached this point, the tree is not visible from the left
  // Check if it is visible from the right
  return vec[index] > tallest;
}
