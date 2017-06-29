/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Lab7
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
void print(Node* head);

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

	print(head);

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

    else if(head->SSN > newSSN)
    {
      Node* insert = new Node;
      insert->SSN = newSSN;
      insert->fullName = newFullName;
      insert->next = head;

      head = insert;
    }

    else
    {
      Node* temp = head;
      Node* insert;

      while(temp->next != NULL && temp->next->SSN < newSSN)
	  {
	   	temp = temp->next;
	  }

   	  insert = new Node;
      insert->SSN = newSSN;
      insert->fullName = newFullName;
      insert->next = NULL;

      if(temp->next != NULL)
      {
     	insert->next = temp->next;
      }

   	  temp->next = insert;
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

void print(Node* head)
{
	Node* temp = head;

	cout << "List contents: " << endl;

	while(temp != NULL)
	{
		cout << temp->SSN << endl;
		temp = temp->next;
	}
}