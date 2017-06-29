#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

struct person {
	string SSN;
	string name;
	person(string SSN, string name){ //constructor
		this->SSN = SSN;
		this->name = name;
	}
};

int main(int argc, char *argv[]){
	vector<struct person> people;
	string leadingChar, SSN, firstName, lastName, inputSSN;
	
	//read the sample.txt file
	ifstream input(argv[1]);
	while (!input.eof()){
		input >> leadingChar >> SSN >> firstName >> lastName; //input each line from the text file into their appropriate variables
		string name = firstName + " " + lastName; //create a full name by combining the first and last name
		people.push_back(person(SSN, name)); //construct a person with their SSN and name and add it to the end of the vector
	}
	input.close();
	
	cout << "Input a SSN" << endl;
	cin >> inputSSN;
	
	//find the index location of the inputted SSN
	for (int i = 0; i < people.size(); i++){
		if (people[i].SSN == inputSSN){ //check if the inputted SSN matches the person's SSN
			cout << "Found at location " << i << endl;
			break;
		}
		else{
			if (i == people.size() - 1){ //the inputted SSN is not in the vector
				cout << "This SSN was not found." << endl;
			}
		}
	}
}