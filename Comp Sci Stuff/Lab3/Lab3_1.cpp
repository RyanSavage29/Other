/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Lab3 Part1
 ******************************/ 

#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	char *word = argv[1];
	int index = atoi(argv[2]) - 1;

	for (int i = strlen(word) - 1; i >= 0; i--)
	{
		if (i != index)
		{
		 cout << word[i];
		}
	}
	cout << endl;
}