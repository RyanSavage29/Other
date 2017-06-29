#include <iostream>
#include <vector>
#include <string.h>
#include <cstdlib>
using namespace std;

bool check(vector<vector<char> > &matrix, char *word, int x, int y){
	for (int i = 0; i < strlen(word); i++){ //loop through every letter in the word
		//go to the next line in the matrix once the current line has ended
		if (x + i >= matrix[y].size()){
			y++;
			x = -i;
		}
		//if the characters do not match, return false
		if (matrix[y][x + i] != word[i]){
			return false;
		}
	}
	
	return true; //every character has matched, so return true
}

int main(int argc, char *argv[]){
	int x;
	int y;
	char *word = argv[1];
	int indexX = atoi(argv[2]);
	int indexY = atoi(argv[3]);
	bool wordFound;
	vector<vector<char> > arr; //create a two-dimensional array
	
	cin >> x; //get the amount of columns
	cin >> y; //get the amount of rows
	
	//make the matrix the correct size
	arr.resize(x);
	for (int i = 0; i < arr.size(); i++){
		arr[i].resize(y);
	}
	
	//fill each character into the matrix
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			char index;
			cin >> index; //read the character
			arr[i][j] = index; //assign the character to the correct index
		}
	}
	
	wordFound = check(arr, word, indexX, indexY); //check to see if the word is present in the matrix
	if (wordFound){
		cout << "True";
	}
	else{
		cout << "False";
	}
	
	return 0; //exit
}