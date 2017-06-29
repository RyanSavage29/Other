/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Project1
 ******************************/ 

#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include "colormod.h"
using namespace std;

void createMatrix(int x, int y, vector< vector<char> > &matrix, vector< vector<bool> > &color)
{
	matrix.resize(x);

	for (int i = 0; i < x; i++)
	{
		matrix[i].resize(y);
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			char letter;
			cin >> letter;
			matrix[i][j] = letter;
		}
	}

	color.resize(x);

	for (int i = 0; i < x; i++)
	{
		color[i].resize(y);
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			color[i][j] = false;
		}
	}
}

bool search(int x, int y, int row, int col, int counter, int length, char *word, vector< vector<char> > &matrix)
{
	counter++;
	if (counter < length)
	{

		cout << endl << counter << " " << length << endl;
		cout << word[counter] << " " << word << endl;
		cout << matrix[row][col] << " " << matrix[row - 1][col + 1] << endl;
		if (row+1 >= matrix[y].size())
			{
				if (matrix[col+1][0] == word[counter])
				{
					row = 0;
					col++;
					search(x, y, row, col, counter, length, word, matrix);
				}
			}

		if (matrix[row+1][col] == word[counter] && row+1 <= x)
		{
			row++;
			search(x, y, row, col, counter, length, word, matrix);
		}

		if (matrix[row+1][col+1] == word[counter] && row+1 <= x && col+1 <= y)
		{
			row++;
			col++;
			search(x, y, row, col, counter, length, word, matrix);
		}

		if (matrix[row][col+1] == word[counter] && col+1 <= y)
		{
			col++;
			search(x, y, row, col, counter, length, word, matrix);
		}

		if (matrix[row-1][col+1] == word[counter] && row-1 >= 0 && col+1 <= y)
		{
			row--;
			col++;
			search(x, y, row, col, counter, length, word, matrix);
		}

		if (matrix[row-1][col] == word[counter] && row-1 >= 0)
		{
			row--;
			search(x, y, row, col, counter, length, word, matrix);
		}

		if (matrix[row-1][col-1] == word[counter] && row-1 >= 0 && col-1 >= 0)
		{
			row--;
			col--;
			search(x, y, row, col, counter, length, word, matrix);
		}

		if (matrix[row][col-1] == word[counter] && col-1 >= y)
		{
			col--;
			search(x, y, row, col, counter, length, word, matrix);
		}

		if (matrix[row+1][col-1] == word[counter] && row+1 <= x && col-1 >= 0)
		{
			cout << "up right" << endl;
			row++;
			col--;
			search(x, y, row, col, counter, length, word, matrix);
		}
	}

	else if (counter == length)
	{
		cout << endl << "true" << endl;
		return true;
	}

	else
	{
		return false;
	}
}

void found(int x, int y, int row, int col, int counter, int length, char *word, vector< vector<char> > &matrix, vector< vector<bool> > &color)
{
	if (counter < length)
	{
		counter++;
		
		if (row+1 >= matrix[y].size())
			{
				if (matrix[0][col+1] == word[counter])
				{
					row = 0;
					col++;
					color[row][col] = true;
					found(x, y, row, col, counter, length, word, matrix, color);
				}
			}

		if (matrix[row+1][col] == word[counter] && row+1 <= x)
		{
			row++;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}

		if (matrix[row+1][col+1] == word[counter] && row+1 <= x && col+1 <= y)
		{
			row++;
			col++;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}

		if (matrix[row][col+1] == word[counter] && col+1 <= y)
		{
			col++;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}

		if (matrix[row-1][col+1] == word[counter] && row-1 >= 0 && col+1 <= y)
		{
			row--;
			col++;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}

		if (matrix[row-1][col] == word[counter] && row-1 >= 0)
		{
			row--;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}

		if (matrix[row-1][col-1] == word[counter] && row-1 >= 0 && col-1 >= 0)
		{
			row--;
			col--;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}

		if (matrix[row][col-1] == word[counter] && col-1 >= y)
		{
			col--;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}

		if (matrix[row+1][col-1] == word[counter] && row+1 <= x && col-1 >= 0)
		{
			row++;
			col--;
			color[row][col] = true;
			found(x, y, row, col, counter, length, word, matrix, color);
		}
	}
}

void check (int x, int y, char *word, vector< vector<char> > &matrix, vector< vector<bool> > &color) 
{
	int counter = 0;
	int length = strlen(word);
	cout << word[0] << " " << word << endl;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cout << matrix[i][j] << " ";
			if (matrix[i][j] == word[0])
			{
				if(search(x, y, i, j, counter, length, word, matrix))
				{
					cout << "check" << endl;
					color[i][j] = true;
					found(x, y, i, j, counter, length, word, matrix, color);
				}
			}
		}
		cout << endl;
	} 
}

void printMatrix(int x, int y, vector< vector<char> > &matrix, vector< vector<bool> > &color)
{
	Color::Setting red(Color::FG_RED);
    Color::Setting def(Color::FG_DEFAULT);

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (color[i][j])
			{
				cout << "red" << matrix[i][j] << " ";
			}
			
			else
			{
				cout << "def" << matrix[i][j] << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cout << color[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	int x, y;
	char* word[argc-1];
	vector<vector<char> > matrix;
	vector<vector<bool> > color;

	for (int i = 1; i < argc; i++)
	{
		word[i-1] = argv[i];
	}

	cin >> x >> y;

	createMatrix(x, y, matrix, color);

	for (int i = 1; i < argc; i++)
	{
		check(x, y, word[i-1], matrix, color);
	}

	printMatrix(x, y, matrix, color);

	return 0;
}