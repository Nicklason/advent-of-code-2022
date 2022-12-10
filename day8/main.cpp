#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::vector<std::vector<int>> createMatrix(int, int);
int findTallestFromLeft(std::vector<std::vector<int>>, int, int);
int findTallestFromRight(std::vector<std::vector<int>>, int, int);
int findTallestFromTop(std::vector<std::vector<int>>, int, int);
int findTallestFromBottom(std::vector<std::vector<int>>, int, int);
bool isVisible(std::vector<std::vector<int>>, int, int);

int main()
{
  int row = 99;
  int column = 99;

  auto vec = createMatrix(row, column);

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
  int visible = row * 2 + (column - 2) * 2;

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
  int size = vec[row][column];

  if (findTallestFromLeft(vec, row, column) < size)
  {
    return true;
  }
  else if (findTallestFromRight(vec, row, column) < size)
  {
    return true;
  }
  else if (findTallestFromTop(vec, row, column) < size)
  {
    return true;
  }
  else if (findTallestFromBottom(vec, row, column) < size)
  {
    return true;
  }

  return false;
}

int findTallestFromLeft(std::vector<std::vector<int>> vec, int row, int column)
{
  int tallest = vec[row][0];
  for (int k = 1; k < column; k++)
  {
    if (vec[row][k] > tallest)
    {
      tallest = vec[row][k];
    }
  }

  return tallest;
}

int findTallestFromRight(std::vector<std::vector<int>> vec, int row, int column)
{
  int columns = vec[row].size();

  int tallest = vec[row][columns - 1];
  for (int k = columns - 2; k > column; k--)
  {
    if (vec[row][k] > tallest)
    {
      tallest = vec[row][k];
    }
  }

  return tallest;
}

int findTallestFromTop(std::vector<std::vector<int>> vec, int row, int column)
{
  int tallest = vec[0][column];
  for (int k = 1; k < row; k++)
  {
    if (vec[k][column] > tallest)
    {
      tallest = vec[k][column];
    }
  }

  return tallest;
}

int findTallestFromBottom(std::vector<std::vector<int>> vec, int row, int column)
{
  int rows = vec.size();

  int tallest = vec[rows - 1][column];
  for (int k = rows - 2; k > row; k--)
  {
    if (vec[k][column] > tallest)
    {
      tallest = vec[k][column];
    }
  }

  return tallest;
}
