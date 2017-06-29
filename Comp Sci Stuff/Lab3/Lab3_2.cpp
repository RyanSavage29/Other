/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Lab3 Part 2
 ******************************/ 

#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	int x, y;
	char *letter = argv[1];
	int indexX = atoi(argv[2]);
  	int indexY = atoi(argv[3]);
	vector<vector<char> > arr;
	
	cin >> x >> y;

	arr.resize(x);

	for (int i = 0; i < x; i++)
	{
		arr[i].resize(y);
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (i == indexY && j == indexX)
			{
				arr[i].push_back(' ');
			}

			char num;
			cin >> num;
			arr[i][j] = num;
		}
	}

	for (int i = arr[indexY].size() - 1; i >= indexX; i--)
	{
		if (i != indexX)
		{
			arr[indexY][i] = arr[indexY][i - 1];
		}

		else
		{
			arr[indexY][i] = *letter;
		}
	}

	for (int i = x - 1; i >= 0; i--)
	{
		for (int j = arr[i].size() - 1; j >= 0; j--)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}