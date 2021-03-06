#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include <string>
#include <time.h>
#include <ctime>

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
  AVLTree tree;
  
  fstream input(argv[1]);
  while(!input.eof()){
    input>> argInput >> SSNInput >> firstNameInput >> lastNameInput;
    fullNameInput = firstNameInput + " " + lastNameInput;
    if(!input) break;
    switch(argInput){
    case 'i'://INSERT
      arguementPerformed = tree.insert(SSNInput, fullNameInput);
      if(arguementPerformed){
	++insertCounter;
      }
      break;
    case 'd'://DELETE
      arguementPerformed = tree.deleteNode(SSNInput);
      if(arguementPerformed){
	++deleteCounter;
      }
      break;
    case 'r'://RETRIEVE
      arguementPerformed = tree.find(SSNInput);
      if(arguementPerformed){
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
  cout<<"Height of the AVL tree: "<<tree.height(tree.getRoot())<<endl;
  cout<<"Time elapsed: "<< duration <<'\n';
  tree.levelOrder();
  return 0;
}
