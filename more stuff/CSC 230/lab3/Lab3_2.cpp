#include <iostream>
#include <vector>
#include <string.h>
#include <cstdlib>
using namespace std;

void addWord(vector<vector<char> > &matrix, char *word, int x, int y){
	int origSize = matrix[y].size();
	int destination;
	
	//input an empty space to be filled later for every letter in the word
	for (int i = 0; i < strlen(word); i++){
		matrix[y].push_back (' ');
	}
	
	destination = matrix[y].size() - origSize - 1 + x; //the index where the word should start being entered
	for (int i = matrix[y].size() - 1; i >= destination; i--){ //loop from the end of the row to where the inputted word will start
		if (i == destination){ //start filling because every letter that needs to be moved has been moved
			//add each letter of the word starting from where specified
			for (int j = 0; j < strlen(word); j++){
				matrix[y][j + x] = word[j];
			}
		}
		else{ 
			matrix[y][i] = matrix[y][origSize - (matrix[y].size() - i)]; //set the current element to the next real letter before
		}
	}
}

int main(int argc, char *argv[]){
	int x;
	int y;
	char *word = argv[1];
	int indexY = atoi(argv[2]);
	int indexX = atoi(argv[3]);
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
	
	addWord(arr, word, indexX, indexY);
	
	//print out the reversed matrix
	for(int i = arr.size() - 1; i >= 0; i--){
		for(int j = arr[i].size() - 1; j >= 0; j--){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	
	return 0; //exit
}