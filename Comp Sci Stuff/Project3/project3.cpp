#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include "DLL.cpp"
using namespace std;

int main(int argc, char* argv[])
{
  clock_t start, end;
  double duration;

  char lead;
  string ssn;
  string firstName;
  string lastName;
  bool found = false;
  string search = "";
  DLL *data = new DLL;
  int insertCount = 0;
  int deleteCount = 0;
  int retrieveCount = 0;
  fstream input(argv[1]);
  int iSlot = 0;
  int dSlot = 0;
  int rSlot = 0;
  struct DataEntry *temp = NULL;

  start = clock();

  while(!input.eof())
    {
      input >> lead >> ssn >> firstName >> lastName;
      if(lead == 'i')
	{
	  found = data->insert(ssn, (firstName + " " + lastName), insertCount);
	}
       else if(lead == 'd')
	 {
	   found = data->remove(ssn, deleteCount);
	 }
      else if(lead == 'r')
	{
	  rSlot = data->search(ssn);
	  if(rSlot != -1)
	    retrieveCount++;
	}
      if(!input)
	break;
    }
  input.close();
  end = clock();
  duration = ( end - start ) / (double)CLOCKS_PER_SEC;

  cout << "The Number of Valid Inseration: " << insertCount << endl;
  cout << "The Number of Valid Deletion: " << deleteCount << endl;
  cout << "The Number of Valid Retrieval: " << retrieveCount << endl;
  cout << "Item numbers in the array: " << data->size() << endl;
  cout << "Time elapsed: " << duration << endl;
}
