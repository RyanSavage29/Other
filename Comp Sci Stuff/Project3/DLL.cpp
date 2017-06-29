#include "DLL.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

// default constructor is already implemented
// do not modify the default constructor
DLL::DLL(){
    headPtr = NULL;
    itemCount=0;
}

// return the head pointer of the list
// it is already implemented, do not modify it
Node* DLL::getHeadPtr(){
    return headPtr;
}

// copy construct, which copies an existing list n
// the new list is a different object from n
// the new list and object n have the same contents
// Please implement it
DLL::DLL(DLL& n)
{
  headPtr = new Node;
  Node* temp = new Node;
  headPtr->succ = temp;
  temp->succ = new Node;
  Node* copier = n.getHeadPtr();
  if(n.getHeadPtr() != NULL)
    {
      while(copier != NULL)
	{
	  temp->ssn = copier->ssn;
	  temp->name = copier->ssn;
	  temp->succ = new Node;
	  temp->succ->pred = temp;
	  temp = temp->succ;
	  copier = copier->succ;
	}
    }
  itemCount = n.size();
}

// destructor
// release every node of the list
// Please implement it
DLL::~DLL()
{
  Node* temp = headPtr->succ;
  while(temp->succ != NULL)
    {
      if(temp->pred != NULL)
	{
	  delete temp->pred;
	}
      temp = temp->succ;
    }
  delete temp;
}

// if some node has SSN matcthes string ss
// return the index value of the node
// the index value of the first node is 0, the second node is 1, etc.
// if there is node matching ss, return -1
int DLL::search(string ss)const
{
  int ans = 0;
  if(headPtr == NULL)
    return-1;
  Node* temp = headPtr->succ;
  while(temp != NULL)
    {
      if(temp->ssn == ss)
	return ans+1;
      temp = temp->succ;
      ans++;
    }
    return -1;
}


// insert (ss, name) to the existing list
// the SSN values are each node are organized in INCREASING order
// if there is a node matching ss value, return false; otherwise true
// else create a node with (ss, name), insert the node to the proper position
// parameter count is the counter of number of valid insertion
// when you implement this method, consider the following situations:
// 1. list is empty
// 2. node should be inserted to the beginning of the list
// 3. node should be inserted to the middle of the list
// 4. node should be inserted to the end of the list

bool DLL::insert(string ss, string name, int & count){
 if(search(ss)==-1)
   {
     Node* newPtr= new Node;
     newPtr->ssn=ss;
     newPtr->name=name;
     newPtr->succ=NULL;
     newPtr->pred=NULL;
     if(headPtr == NULL)
       {
	 headPtr = newPtr;
	 itemCount++;
       }
     else if((headPtr->ssn).compare(ss)>0)
       {
	 Node* temp=headPtr;
	 headPtr=newPtr;
	 headPtr->succ=temp;
	 temp->pred=headPtr;
       }
     else
       {
	 Node* temp=headPtr;
	 Node* temp2=NULL;
	 while(temp->succ!=NULL)
	   {
	     if(((temp->succ)->ssn).compare(ss)>0)
	       {
		 temp2=temp->succ;
		 temp->succ=newPtr;
		 newPtr->succ=temp2;
		 newPtr->pred=temp;
		 temp2->pred=newPtr;
		 break;
	       }
	     temp=temp->succ;
	   }
	 temp->succ=newPtr;
	 newPtr->pred=temp;
       }
     count++;
     itemCount++;
     return true;
   }
 else
   {
     return false;
   }
}


// remove node containing ss value
// if there is no node containing ss, return false; otherwise true
// consider the following situations:
// 1. list is empty
// 2. node containing ss value is the first node
// 3. node containing ss value is in the middle of the list
// 4. node containing ss value is the last node of the list
bool DLL::remove(string ss, int & count)
{
  if(headPtr == NULL)
    {
      return false;
    }
  else
    {
      Node* temp = headPtr->succ;
      while(temp != NULL)
	{
	  if(temp->ssn == ss)
	    {
	      temp->pred->succ = temp->succ;
	      if(temp->succ != NULL)
		temp->succ->pred = temp->pred;
	      delete temp;
	      count++;
	      itemCount--;
	      return true;
	    }
	  temp = temp->succ;
	} 
    }
  return false;
}

// return the number of the nodes
// it is already implemented, do not modify it
int DLL::size(){
    
    return itemCount;
}

// iterate through each node
// print out SSN and memory address of each node
// do not modify this method
void DLL::display(){
    Node* temp;
    temp = headPtr;
    while (temp!= NULL) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}
