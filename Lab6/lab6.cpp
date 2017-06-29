#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Node
{
  string dssn;
  string dfullName;
  Node* next;
};
void append(Node*& head, string nssn, string nfullName)
{
  if(head == NULL)
    {
      head = new Node;
      head->dssn = nssn;
      head->dfullName = nfullName;
      head->next = NULL;
    }
  else
    {
      Node*& temp = head;
      while(temp->next != NULL)
	{
	  temp = temp->next;
	}
      temp->next = new Node;
      temp->next->dssn = nssn;
      temp->next->dfullName = nfullName;
      cout << temp->next->dssn << endl;
    }
}
int searcher(Node* head, string ssn)
{
  int counter = 0;
  Node* temp = head;
  while(temp != NULL)
    {
      if(temp->dssn == ssn)
	{
	  return counter;
	}
      temp = temp->next;
      counter++;
    }
  return -1;
}
int main(int argc, char* argv[])
{
  char lead;
  string ssn;
  string firstName;
  string lastName;
  bool found = false;
  string search = "";

  Node* headptr = NULL;
  int count = 0;
  fstream input(argv[1]);
  int slot = 0;
  Node* seriesPtr = NULL;
  while(!input.eof())
    {
      input >> lead >> ssn >> firstName >> lastName;
      append(headptr, ssn, (firstName + " " + lastName));
      count++;
      if(!input)
	break;
    }
  input.close();
  cout << "input a SSN;" << endl;
  cin >> search;
  // slot = searcher(headptr, search);
  seriesPtr = headptr;
  for(int i = 0; i < count; i++)
    {
      if(search.compare(seriesPtr->dssn) == 0)
	{
	  found = true;
	  slot = i;
	  i = count;
	}
    }
  if(!found)
    cout << "SSN not found" << endl;
  else
    cout << "SSN found in slot " << slot << endl;
}
