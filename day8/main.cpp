#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::vector<std::vector<int>> createMatrix(int, int);

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
      // std::cout << "i: " << i << " j: " << j << " height: " << vec[i][j] << std::endl;

      // Find biggest tree on the left
      int left = vec[i][0];
      for (int k = 1; k < j; k++)
      {
        if (vec[i][k] > left)
        {
          left = vec[i][k];
        }
      }

      if (left < vec[i][j])
      {
        // std::cout << "visible from left" << std::endl;
        visible++;
        continue;
      }

      // Find biggest tree on the right
      int right = vec[i][column - 1];
      for (int k = column - 2; k > j; k--)
      {
        if (vec[i][k] > right)
        {
          right = vec[i][k];
        }
      }

      if (right < vec[i][j])
      {
        // std::cout << "visible from right" << std::endl;
        visible++;
        continue;
      }

      int top = vec[0][j];
      for (int k = 1; k < i; k++)
      {
        if (vec[k][j] > top)
        {
          top = vec[k][j];
        }
      }

      if (top < vec[i][j])
      {
        // std::cout << "visible from top" << std::endl;
        visible++;
        continue;
      }

      int bottom = vec[row - 1][j];
      for (int k = row - 2; k > i; k--)
      {
        if (vec[k][j] > bottom)
        {
          bottom = vec[k][j];
        }
      }

      if (bottom < vec[i][j])
      {
        // std::cout << "visible from bottom" << std::endl;
        visible++;
        continue;
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
