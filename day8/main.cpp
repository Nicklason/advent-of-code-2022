#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::vector<std::vector<int>> createMatrix(int, int);
std::vector<int> getRow(std::vector<std::vector<int>>, int);
std::vector<int> getColumn(std::vector<std::vector<int>>, int);
bool isVisibleInRow(std::vector<int>, int);
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

std::vector<int> getRow(std::vector<std::vector<int>> vec, int row)
{
  return vec[row];
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

bool isVisible(std::vector<std::vector<int>> vec, int row, int column)
{
  return isVisibleInRow(getRow(vec, row), column) || isVisibleInRow(getColumn(vec, column), row);
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
