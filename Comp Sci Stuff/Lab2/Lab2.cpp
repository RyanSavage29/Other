/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Lab2
 ******************************/ 

#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
using namespace std;

bool check (vector< vector<char> > &matrix, char *word, int x, int y) 
{
	for (int i = 0; i < strlen(word); i++)
	{
		if (i + x >= matrix[y].size())
		{
			y++;
			x = -i;
		}

		if (matrix[y][i+x] != word[i])
		{
			return false;
		}
	} 
	return true;
}

int main(int argc, char *argv[])
{
	int x, y;
	char *search = argv[1];
	int startX = atoi(argv[2]);
  	int startY = atoi(argv[3]);
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
			char num;
			cin >> num;
			arr[i][j] = num;
		}
	}

	bool match = check(arr, search, startX, startY);

	if (match)
	{
		cout << "The output is true." << endl;
	}

	else
	{
		cout << "The output is false." << endl;
	}

	return 0;
}