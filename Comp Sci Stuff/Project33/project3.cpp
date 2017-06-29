#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <ctime>
#include "DLL.h"
using namespace std;

int main(int argc, char* argv[]){
  clock_t start, end;
  double duration;
  start = clock();
  int insertCounter = 0, deleteCounter = 0, retrieveCounter = 0;
  string firstNameInput, lastNameInput, SSNInput, userSSN, fullNameInput;
  char argInput;
  int indexFound;
  bool arguementPerformed = false;
  DLL myList;
  
  fstream input(argv[1]);
  while(!input.eof()){
    input>> argInput >> SSNInput >> firstNameInput >> lastNameInput;
	fullNameInput = firstNameInput + " " + lastNameInput;
    if(!input) break;
    switch(argInput){
		case 'i'://INSERT
		arguementPerformed = myList.insert(SSNInput, fullNameInput, insertCounter);
		break;
		case 'd'://DELETE
		arguementPerformed = myList.remove(SSNInput, deleteCounter);
		break;
		case 'r'://RETRIEVE find out what this needs to do
		indexFound = myList.search(SSNInput);
		if(indexFound != -1){
			++retrieveCounter;
		}
		break;
		default:
		cout << "Unknown command. Check file." << endl;
		break;
	}
  }
  input.close();

  end = clock();
  duration = ( end - start ) / (double) CLOCKS_PER_SEC;
  cout<<"The Number of Valid Insertation :" << insertCounter <<endl;
  cout<<"The Number of Valid Deletion :" << deleteCounter <<endl;
  cout<<"The Number of Valid Retrieval :" << retrieveCounter <<endl;
  cout<<"Size of the list :"<< myList.size() <<endl;
  cout<<"Time elapsed: "<< duration <<'\n';
  return 0;
}