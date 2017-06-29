/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Project2
 ******************************/ 

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

struct Person{
	  string SSN;
	  string name;
};

bool insertPerson(Person* list, string SSNInput, string fullName, int filledSized);
bool deletePerson(Person* list, string SSNInput, string fullName, int filledSized);
bool retrievePerson(Person* list, string SSNInput, string fullName, int filledSized);

int main(int argc, char* argv[]){
  clock_t start, end;
  double duration;
  start = clock();
  int insertCounter = 0, deleteCounter = 0, retrieveCounter = 0;
  int personCounter = 0;
  string firstNameInput, lastNameInput, SSNInput, userSSN, fullNameInput;
  char argInput;
  bool arguementPerformed = false;
  
  Person *personList = new Person[1000];
  int currentArraySize = 1000;
  Person *tempArray;
  
  fstream input(argv[1]);
  while(!input.eof()){
    input>> argInput >> SSNInput >> firstNameInput >> lastNameInput;
	fullNameInput = firstNameInput + " " + lastNameInput;
    if(!input) break;
    switch(argInput){
		case 'i'://INSERT
		arguementPerformed = insertPerson(&personList[0], SSNInput, fullNameInput, personCounter);
		if(arguementPerformed){
			++insertCounter;
			++personCounter;
			if(personCounter == currentArraySize){//Increases array size if needed
			  tempArray = new Person[currentArraySize * 2];
			  for(int i = 0; i < personCounter; ++i){
			    tempArray[i] = personList[i];
			  }
			  delete [] personList;
			  personList = tempArray;
			  currentArraySize = currentArraySize * 2;
			}
		}
		break;
		case 'd'://DELETE
		arguementPerformed = deletePerson(&personList[0], SSNInput, fullNameInput, personCounter);
		if(arguementPerformed){
			++deleteCounter;
			--personCounter;
			if(personCounter < (currentArraySize / 4)){//Decreases array size if needed
			  tempArray = new Person[currentArraySize / 2];
			  for(int i = 0; i < personCounter; ++i){
			    tempArray[i] = personList[i];
			  }
			  delete [] personList;
			  personList = tempArray;
			  currentArraySize = currentArraySize / 2;
			}
		}
		break;
		case 'r'://RETRIEVE
		arguementPerformed = retrievePerson(&personList[0], SSNInput, fullNameInput, personCounter);
		if(arguementPerformed){
			++retrieveCounter;
		}
		break;
		default:
		cout << "Unknown command. Check file." << endl;
		break;
	}
	arguementPerformed = false;
  }
  input.close();

  end = clock();
  duration = ( end - start ) / (double) CLOCKS_PER_SEC;
  cout<<"The Number of Valid Insertation :" << insertCounter <<endl;
  cout<<"The Number of Valid Deletion :" << deleteCounter <<endl;
  cout<<"The Number of Valid Retrieval :" << retrieveCounter <<endl;
  cout<<"Item numbers in the array :"<< personCounter <<endl;
  cout<<"Array Size is :"<< currentArraySize <<endl;
  cout<<"Time elapsed: "<< duration <<'\n';
  return 0;
}
//insert function
bool insertPerson(Person* personList, string SSNInput, string fullName, int filledSized){
	bool check = true;
	for(int i = 0; i < filledSized; ++i){
		if(SSNInput.compare(personList[i].SSN) == 0 || fullName.compare(personList[i].name) == 0){
			check = false;
			break;
		}
	}
	if(check){
		personList[filledSized].SSN = SSNInput;
		personList[filledSized].name = fullName;
	}
	return check;
}
//delete function
bool deletePerson(Person* personList, string SSNInput, string fullName, int filledSized){
	bool check = false;
	for(int i = 0; i < filledSized; ++i){
		if(SSNInput.compare(personList[i].SSN) == 0 && fullName.compare(personList[i].name) == 0){
			check = true;
			for(int j = i; j <filledSized; ++j){
				personList[j].SSN = personList[j+1].SSN;
				personList[j].name = personList[j+1].name;
			}
			break;
		}
	}
	return check;
}
//retrieval function
bool retrievePerson(Person* personList, string SSNInput, string fullName, int filledSized){
	bool check = false;
	for(int i = 0; i < filledSized; ++i){
		if(SSNInput.compare(personList[i].SSN) == 0 && fullName.compare(personList[i].name) == 0){
			check = true;
			break;
		}
	}
	return check;
}