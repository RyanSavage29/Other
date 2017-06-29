/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Lab5
 ******************************/ 

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Node
{
	string SSN;
	string fullName;
	Node* next;
};

void append(Node*& head, string newSSN, string newFullName);
int search(Node* head, string findSSN);

int main(int argc, char* argv[])
{
	char leadChar;
	string firstName, lastName, listSSN, searchSSN;
	int check;
	bool found = false;

	Node* head = NULL;

	fstream input(argv[1]);
	while(!input.eof())
	{
	  input >> leadChar >> listSSN >> firstName >> lastName;

	  append(head, listSSN, (firstName + " " + lastName));
	}
	input.close();

	cout << "Input a SSN" << endl;
	cin >> searchSSN;

	check = search(head, searchSSN);

	if(check < 0)
	{
		cout << "Could not find SSN" << endl;
	}
	
	else
	{
		cout << "Found at location " << check << endl;
	}

	return 0;
}

void append(Node*& head, string newSSN, string newFullName)
{
	if(head == NULL)
    {
      head = new Node;
      head->SSN = newSSN;
      head->fullName = newFullName;
      head->next = NULL;
    }

  else
  {
    Node* temp = head;

    while(temp->next != NULL)
	{
		temp = temp->next;
	}

   	temp->next = new Node;
    temp->next->SSN = newSSN;
    temp->next->fullName = newFullName;
    temp->next->next = NULL;
  }
}

int search(Node* head, string findSSN)
{
	Node* temp = head;
	int counter = 0;

	while(temp != NULL)
	{
		if(temp->SSN == findSSN)
		{
			return counter;
		}

		temp = temp->next;
		counter++;
	}

	return -1;
}