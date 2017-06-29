#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){
	char *word = argv[1];
	int pos = atoi(argv[2]);
	
	for (int i = strlen(word) - 1; i >= 0; i--){ //loop through each letter starting from the final letter
		//print out every letter except for the one specified
		if (i != pos - 1){
			cout << word[i];
		}
	}
	
	return 0; //exit
}