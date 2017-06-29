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

struct Person
{
	  string SSN;
	  string name;
};

bool insertPerson(Person* list, string listSSN, string fullName, int filledSized);
bool deletePerson(Person* list, string listSSN, string fullName, int filledSized);
bool retrievePerson(Person* list, string listSSN, string fullName, int filledSized);
int increaseArray(Person* list, int filledSized, int currentSize);
int decreaseArray(Person* list, int filledSized, int currentArraySize);

//insert function
bool insertPerson(Person* personList, string SSNInput, string fullName, int filledSized)
{
	bool check = true;
	for(int i = 0; i < filledSized; i++)
	{
		if(SSNInput.compare(personList[i].SSN) == 0 || fullName.compare(personList[i].name) == 0)
		{
			check = false;
			break;
		}
	}
	
	if(check)
	{//likely has something to do at the index following what should be the last filled index, namely that it doesnt seem to exist
		personList[filledSized].SSN = SSNInput;
		cout <<" pi";
		personList[filledSized].name = fullName;
		cout << " wtf";
	}
	return check;
}
//delete function
bool deletePerson(Person* personList, string SSNInput, string fullName, int filledSized)
{
	bool check = false;
	for(int i = 0; i < filledSized; ++i){
		if(SSNInput.compare(personList[i].SSN) == 0 && fullName.compare(personList[i].name) == 0)
		{
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
bool retrievePerson(Person* personList, string SSNInput, string fullName, int filledSized)
{
	bool check = false;
	for(int i = 0; i < filledSized; ++i){
		if(SSNInput.compare(personList[i].SSN) == 0 && fullName.compare(personList[i].name) == 0)
		{
			check = true;
			break;
		}
	}
	return check;
}
//resizes the array when needed
int increaseArray(Person* personList, int filledSized, int currentArraySize)
{
	if(filledSized == currentArraySize)
	{
		cout<<"UPSIZING"<<endl;
		Person tempArray[currentArraySize * 2];
		for(int i = 0; i < filledSized; i++)
		{
			tempArray[i] = personList[i];
		}
		delete [] personList;
		personList = new Person[currentArraySize * 2];
		for(int i = 0; i < filledSized; i++)
		{
			personList[i] = tempArray[i];
		}
		delete [] tempArray;
		return currentArraySize * 2;
	}
	//this is returned if no change is needed
	return currentArraySize;
}
//resizes the array when needed

int decreaseArray(Person* personList, int filledSized, int currentArraySize)
{
	if(filledSized < (currentArraySize / 4))
	{
		cout<<"DESIZING"<<endl;
		Person tempArray[currentArraySize / 2];
		for(int i = 0; i < filledSized; i++)
		{
			tempArray[i] = personList[i];
		}
		delete [] personList;
		personList = new Person[currentArraySize / 2];
		for(int i = 0; i < filledSized; i++)
		{
			personList[i] = tempArray[i];
		}
		delete [] tempArray;
		return currentArraySize / 2;
	}
	//this is returned if no change is needed
	return currentArraySize;
}

int main(int argc, char* argv[])
{
  clock_t start, end;
  double duration;
  start = clock();
  int insertCounter = 0, deleteCounter = 0, retrieveCounter = 0;
  int personCounter = 0;
  string firstName, lastName, fullName, listSSN;
  char leadChar;
  bool leadCharCheck = false;

  
  Person *list = new Person[1000];
  int currentArraySize = 1000;
  int tempQ = currentArraySize;

  fstream input(argv[1]);
  while(!input.eof())
  {
    input >> leadChar >> listSSN >> firstName >> lastName;
	fullName = firstName + " " + lastName;
    
    if(!input)
    {
    	break;
    }
	//TEST CODE
	cout << leadChar << " " << currentArraySize << " " << fullName << " " << personCounter << " ";
	//END TEST CODE
    switch(leadChar)
    {
		case 'i'://INSERT
		
		
			if (tempQ != currentArraySize)
			{
				personCounter--;
				tempQ = currentArraySize;
			}
			currentArraySize = increaseArray(&list[0], personCounter, currentArraySize);
		leadCharCheck = insertPerson(&list[0], listSSN, fullName, personCounter);
		if(leadCharCheck)
		{


			if (currentArraySize)
			cout << "Was Inserted" << endl;
			insertCounter++;
			personCounter++;
			//currentArraySize = increaseArray(&list[0], personCounter, currentArraySize); //RESIZE FUNCTION
		}
		break;

		case 'd'://DELETE
		leadCharCheck = deletePerson(&list[0], listSSN, fullName, personCounter);
		if(leadCharCheck)
		{
			cout << "Was Deleted" << endl;
			deleteCounter++;
			personCounter--;
			currentArraySize = decreaseArray(&list[0], personCounter, currentArraySize); //RESIZE FUNCTION
		}
		break;

		case 'r'://RETRIEVE
		leadCharCheck = retrievePerson(&list[0], listSSN, fullName, personCounter);
		if(leadCharCheck)
		{
			cout << "Was Retrieved" << endl;
			retrieveCounter++;
		}
		break;

		default:
		cout << "" << endl;
		break;
	}
	leadCharCheck = false;
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