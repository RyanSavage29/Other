#include "DLL.h"
#include <iostream>
#include <string>
using namespace std;

//default constructor
DLL::DLL(){
    headPtr = NULL;
    itemCount=0;
}

//returns headPTR
Node* DLL::getHeadPtr(){
    return headPtr;
}

// copy construct, which copies an existing list n
DLL::DLL(DLL& n){
	Node* copiedList = n.headPtr;
	Node* newListPtr;
	if(copiedList == NULL){
		headPtr = NULL;
		return;
	}
	newListPtr = new Node;
	headPtr = newListPtr;
	headPtr->ssn = copiedList->ssn;
	headPtr->name = copiedList->name;
	headPtr->pred = NULL;
	headPtr->succ = NULL;
	Node* temp = headPtr;
	copiedList = copiedList->succ;
	while(copiedList != NULL){
		newListPtr = new Node;
		temp->succ = newListPtr;
		temp->succ->pred = temp;
		temp = temp->succ;
		temp->ssn = copiedList->ssn;
		temp->name = copiedList->name;
		temp->succ = NULL;
		copiedList = copiedList->succ;
	}
	return;
}

//DONE FOR NOW
//deconstructor
DLL::~DLL(){
	if(headPtr == NULL){
		return;
	}
	Node* temp = headPtr;
	while(temp->succ != NULL){
		temp = temp->succ;
		delete temp->pred;
	}
	delete temp;
	return;
}

//searches for the index of a specified ssn
//returns -1 if it does not exist
int DLL::search(string ss)const{
	Node* temp = headPtr;
	int index = 0;
	while(temp != NULL){
		if(ss.compare(temp->ssn) == 0){
			return index;
		}
		++index;
		temp = temp->succ;
	}
	return -1;
}


// insert (ss, name) to the existing list
// the SSN values are each node are organized in INCREASING order
// if there is a node matching ss value, return false; otherwise true
// else create a node with (ss, name), insert the node to the proper position
// parameter count is the counter of number of valid insertion
bool DLL::insert(string ss, string name, int & count){
    Node* temp = headPtr;
	Node* newNode = new Node;
	newNode->ssn = ss;
	newNode->name = name;
	newNode->succ = NULL;
	newNode->pred = NULL;
	if(headPtr == NULL){//inserts if the list is empty
		headPtr = newNode;
		++count;
		++itemCount;
		return true;
	}
	if(newNode->ssn.compare(headPtr->ssn) <= 0){//inserts at the front of the list if the ssn is lower than the current first
		if(newNode->ssn.compare(headPtr->ssn) == 0){//does not insert if the ssn is already inside
			delete newNode;
			return false;
		}
		newNode->succ = headPtr;
		headPtr->pred = newNode;
		headPtr = newNode;
		++count;
		++itemCount;
		return true;
	}
	while(temp->succ != NULL && newNode->ssn.compare(temp->succ->ssn) >= 0){//iterates until it reaches a spot to insert
		if(newNode->ssn.compare(temp->succ->ssn) == 0){//if the ssn exists already, delets the node and returns false
			delete newNode;
			return false;
		}
		temp = temp->succ;
    }
    newNode->succ = temp->succ;
	if(temp->succ != NULL){//testing this, put in right place
		temp->succ->pred = newNode;
	}
    temp->succ = newNode;
	newNode->pred = temp;
	++count;
	++itemCount;
	return true;
}


// remove node containing ss value
// if there is no node containing ss, return false; otherwise true
//test removing end item, beginning item returns fine.
bool DLL::remove(string ss, int & count){
	Node* temp;
	if(headPtr == NULL){
		return false;
	}
	if(ss.compare(headPtr->ssn) == 0){
		if(headPtr->succ != NULL){
			headPtr->succ->pred = NULL;
			temp = headPtr->succ;
			delete headPtr;
			headPtr = temp;
		}
		else{
			headPtr = NULL;
		}
		++count;
		--itemCount;
		return true;
	}
	temp = headPtr->succ;
	while(temp != NULL){
		if(ss.compare(temp->ssn) == 0){
			temp->pred->succ = temp->succ;
			if(temp->succ != NULL){
				temp->succ->pred = temp->pred;
			}
			delete temp;
			++count;
			--itemCount;
			return true;
		}
		temp = temp->succ;
	}
    return false;
}

//returns the size of the list
int DLL::size(){
    return itemCount;
}

//Prints out the list
void DLL::display(){
    Node* temp;
    temp = headPtr;
    while (temp!= NULL) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}
