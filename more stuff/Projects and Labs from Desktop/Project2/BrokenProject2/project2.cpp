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

bool insertPerson(Person* personList, string SSNInput, string fullName, int filledSized);
bool deletePerson(Person* personList, string SSNInput, string fullName, int filledSized);
bool retrievePerson(Person* personList, string SSNInput, string fullName, int filledSized);
int increaseArray(Person* personList, int filledSized, int currentArraySize);
int decreaseArray(Person* personList, int filledSized, int currentArraySize);

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
  
  fstream input(argv[1]);
  while(!input.eof()){
    input>> argInput >> SSNInput >> firstNameInput >> lastNameInput;
	fullNameInput = firstNameInput + " " + lastNameInput;
    if(!input) break;
	//TEST CODE
	//cout<< fullNameInput <<" "<< SSNInput << argInput <<endl;
	//END TEST CODE
    switch(argInput){
		case 'i'://INSERT
		arguementPerformed = insertPerson(&personList[0], SSNInput, fullNameInput, personCounter);
		if(arguementPerformed){
			++insertCounter;
			++personCounter;
			currentArraySize = increaseArray(&personList[0], personCounter, currentArraySize); //RESIZE FUNCTION
		}
		break;
		case 'd'://DELETE
		arguementPerformed = deletePerson(&personList[0], SSNInput, fullNameInput, personCounter);
		if(arguementPerformed){
			++deleteCounter;
			--personCounter;
			currentArraySize = decreaseArray(&personList[0], personCounter, currentArraySize); //RESIZE FUNCTION
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
  /*TEST CODE
  for(int i = 0; i < personCounter; ++i){
	  cout<< personList[i].name <<" "<< personList[i].SSN <<endl;
  }
  END TEST CODE*/
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
	if(check){//likely has something to do at the index following what should be the last filled index, namely that it doesnt seem to exist
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
//resizes the array when needed
int increaseArray(Person** personList, int filledSized, int currentArraySize){
	if(filledSized == currentArraySize){
		cout<<"UPSIZING"<<endl;
		Person* tempArray = new Person[currentArraySize * 2];
		for(int i = 0; i < filledSized; ++i){
			tempArray[i] = personList[i];
		}
		delete [] personList;
		personList = tempArray;
		return currentArraySize * 2;
	}
	//this is returned if no change is needed
	return currentArraySize;
}
//resizes the array when needed

int decreaseArray(Person* personList, int filledSized, int currentArraySize){
	if(filledSized < (currentArraySize / 4)){
		cout<<"DESIZING"<<endl;
		Person tempArray[currentArraySize / 2];
		for(int i = 0; i < filledSized; ++i){
			tempArray[i] = personList[i];
		}
		delete [] personList;
		personList = tempArray;
		return currentArraySize / 2;
	}
	//this is returned if no change is needed
	return currentArraySize;
}