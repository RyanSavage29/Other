/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Lab4
 ******************************/ 

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct person
{
	string SSN;
	string name;
};

int main(int argc, char *argv[])
{
	char leadChar;
	string firstName, lastName, listSSN, searchSSN;
	int counter = 0;
	bool found = false;

	vector<person > list;
	list.resize(1000);

	fstream input(argv[1]);
	while(!input.eof())
	{
		input >> leadChar >> listSSN >> firstName >> lastName;

		list[counter].SSN = listSSN;
		list[counter].name = firstName + " " + lastName;

		counter++;
	}
	input.close();

	cout << "Input a SSN" << endl;
	cin >> searchSSN;

	for (int i = 0; i < counter; i++)
	{
		if(searchSSN.compare(list[i].SSN) == 0)
		{
			cout << "Found at location " << i << endl;
			found = true;
			break;
		}
	}

	if (!found)
	{
			cout << "Could not find SSN" << endl;
	}

	return 0;
}