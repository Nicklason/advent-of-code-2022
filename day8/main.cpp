#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::vector<std::vector<int>> createMatrix(int, int);
bool isVisibleInRow(std::vector<std::vector<int>>, int, int);
bool isVisibleInColumn(std::vector<std::vector<int>>, int, int);
bool isVisible(std::vector<std::vector<int>>, int, int);

int main()
{
  int rows = 99;
  int columns = 99;

  auto vec = createMatrix(rows, columns);

  // Populate the matrix

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

  // All outside trees can be seen
  int visible = rows * 2 + (columns - 2) * 2;

  // Loop through all inner trees and check if they can be seen
  for (int i = 1; i < vec.size() - 1; i++)
  {
    for (int j = 1; j < vec[i].size() - 1; j++)
    {
      // Check if tree is visible from any direction
      if (isVisible(vec, i, j))
      {
        visible++;
      }
    }
  }

  std::cout << visible << std::endl;

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

bool isVisible(std::vector<std::vector<int>> vec, int row, int column)
{
  return isVisibleInRow(vec, row, column) || isVisibleInColumn(vec, row, column);
}

bool isVisibleInRow(std::vector<std::vector<int>> vec, int row, int column)
{
  int tallest = vec[row][0];

  bool isVisible = false;

  // Loop through all trees in the same row
  for (int k = 1; k < vec[row].size(); k++)
  {
    // Check if we reached the current tree
    if (k == column)
    {
      // Check if tree is visible from left
      if (vec[row][k] > tallest)
      {
        // Tree is visible, so we can skip the rest of the trees in the row
        return true;
      }

      // Tree is not visible, reset tallest and continue to check from the right
      tallest = 0;
      continue;
    }

    // Check if tree is taller than the current tallest tree
    if (vec[row][k] > tallest)
    {
      tallest = vec[row][k];
    }
  }

  // If we reached this point, the tree is not visible from the left
  // Check if it is visible from the right
  return vec[row][column] > tallest;
}

bool isVisibleInColumn(std::vector<std::vector<int>> vec, int row, int column)
{
  int tallest = vec[0][column];

  // Loop through all trees in the same column
  for (int k = 1; k < vec.size(); k++)
  {
    if (k == row)
    {
      // Check if tree is visible from top
      if (vec[k][column] > tallest)
      {
        return true;
      }

      tallest = 0;
      continue;
    }

    if (vec[k][column] > tallest)
    {
      tallest = vec[k][column];
    }
  }

  return vec[row][column] > tallest;
}
