/* Danny Beer
   CSC 230-03
   Project 1   */

#include "colormod.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

void getBounds(int matrixSize, int x, int y, int &xLeftBound, int &xRightBound, int &yUpperBound, int &yLowerBound){
	//if the current letter is in the left-most column, do not allow the program to check to the left of it
	if (x > 0){
		xLeftBound = x - 1;
	}
	else{
		xLeftBound = x;
	}
	
	//if the current letter is in the right-most column, do not allow the program to check to the right of it
	if (x < matrixSize - 1){
		xRightBound = x + 1;
	}
	else{
		xRightBound = matrixSize - 1;
	}
	
	//if the current letter is in the top row, do not allow the program to check above it
	if (y > 0){
		yUpperBound = y - 1;
	}
	else{
		yUpperBound = y;
	}
	
	//if the current letter is in the bottom row, do not allow the program to check below it
	if (y < matrixSize - 1){
		yLowerBound = y + 1;
	}
	else{
		yLowerBound = matrixSize - 1;
	}
}

void printColoredLettersMatrix(vector<vector<char> > &matrix, vector<vector<bool> > &redLetters){
	Color::Setting red(Color::FG_RED);
	Color::Setting def(Color::FG_DEFAULT);
	
	//print the matrix, giving each character its appropriate color
	for (int i = 0; i < matrix.size(); i++){
		for (int j = 0; j < matrix[i].size(); j++){
			if (redLetters[i][j]){ //if the coordinate was used to form a word
				cout << red << matrix[i][j] << " "; //print out a red character
			}
			else{
				cout << def << matrix[i][j] << " "; //print out a default colored character
			}
		}
		cout << endl;
	}
}

void checkSurroundingLetters(vector<vector<char> > &matrix, vector<vector<bool> > &redLetters, char *word, int letterIndex, vector<int> &usedX, vector<int> &usedY){
	if (letterIndex < strlen(word)){ //stop recursion when last letter is reached
		int x = usedX[usedX.size() - 1]; //find the current letter's x-coordinate
		int y = usedY[usedY.size() - 1]; //find the current letter's y-coordinate
		int xLeftBound, xRightBound, yUpperBound, yLowerBound;
		
		getBounds(matrix.size(), x, y, xLeftBound, xRightBound, yUpperBound, yLowerBound);		
				
		for (int i = yUpperBound; i <= yLowerBound; i++){		
			for (int j = xLeftBound; j <= xRightBound; j++){
				if (matrix[i][j] == word[letterIndex]){ //check if the next letter of the word matches the coordinate's character
					if (!redLetters[i][j]){ //allow the multiple instances of the same word to use the same letters
						for (int l = 0; l < usedX.size(); l++){ //loop through every coordinate that has been recorded for the current word
							if (i == usedY[l] && j == usedX[l]){ //make sure the space has not been used yet
								break; //stop looping because the space has been used
							}
							else{
								if (l == usedX.size() - 1){ //the space has not been used
									usedX.push_back(j); //add the x-coordinate of the next letter
									usedY.push_back(i); //add the y-coordinate of the next letter
									checkSurroundingLetters(matrix, redLetters, word, letterIndex + 1, usedX, usedY);
								}
							}
						}
					}
					else{
						usedX.push_back(j); //add the x-coordinate of the next letter
						usedY.push_back(i); //add the y-coordinate of the next letter
						checkSurroundingLetters(matrix, redLetters, word, letterIndex + 1, usedX, usedY);
					}
				}
				else{ //the coordinate's character does not match the next letter of the word
					if (i == yLowerBound && j == xRightBound){ //if every viable character has been checked (other than skip line if applicable)
						//*process for skipping a line*
						if (xRightBound == x && yLowerBound != matrix.size() - 1){ //if the current letter was in the right-most column, bbut not in the bottom right corner
							if (matrix[y + 1][0] == word[letterIndex]){ //check if the next letter of the word matches the character on the next line (skip a line)
								if (!redLetters[i][j]){ //allow the multiple instances of the same word to use the same letters
									for (int l = 0; l < usedX.size(); l++){ //loop through every coordinate that has been recorded for the current word
										if (y + 1 == usedY[l] && 0 == usedX[l]){ //make sure the space has not been used yet
											//remove the current character's coordinates as the word can be completed on the current path
											usedX.pop_back();
											usedY.pop_back();
											break; //stop looping because the space has been used
										}
										else{
											if (l == usedX.size() - 1){ //the space has not been used
												usedX.push_back(0); //add the x-coordinate of the next letter
												usedY.push_back(y + 1); //add the y-coordinate of the next letter
												checkSurroundingLetters(matrix, redLetters, word, letterIndex + 1, usedX, usedY);
											}
										}
									}
								}
								else{
									usedX.push_back(j); //add the x-coordinate of the next letter
									usedY.push_back(i); //add the y-coordinate of the next letter
									checkSurroundingLetters(matrix, redLetters, word, letterIndex + 1, usedX, usedY);
								}
							}
							else{ //the space's character did not match the desired letter
								//remove the current character's coordinates as the word can be completed on the current path
								usedX.pop_back();
								usedY.pop_back();
							}
						}
						else{
							//remove the current character's coordinates as the word can be completed on the current path
							usedX.pop_back();
							usedY.pop_back();
						}
					}
				}
			}
		}
	}
	else{
		for (int i = 0; i < usedX.size(); i++){
			redLetters[usedY[i]][usedX[i]] = true; //store the information that the letters of this word are red
		}
	}
}

void findStartingLetter(vector<vector<char> > &matrix, vector<vector<bool> > &redLetters, char *word[], int numberOfWords){
	for (int i = 0; i < matrix.size(); i++){
		for (int j = 0; j < matrix[i].size(); j++){
			for (int l = 0; l < numberOfWords; l++){ //check each word's first letter
				if (matrix[i][j] == word[l][0]){
					vector<int> usedX, usedY; //create a vector for x-values and a vector for y-values where (x, y) should be red
					usedX.push_back(j);
					usedY.push_back(i);
					checkSurroundingLetters(matrix, redLetters, word[l], 1, usedX, usedY);
				}
			}
		}
	}
}

int main(int argc, char *argv[]){
	int x;
	int y;
	int numberOfWords = argc - 1;
	char *word[numberOfWords];
	vector<vector<char> > arr; //create a two-dimensional array for the matrix file
	vector<vector<bool> > redLetters; //create a two-dimensional array to store which letters are redLetters and which are not
	
	//filter every desiredLetters word into an array;
	for (int i = 1; i < argc; i++){
		word[i - 1] = argv[i];
	}
	
	cin >> x; //get the amount of columns
	cin >> y; //get the amount of rows
	
	//make the matrix the correct size
	arr.resize(x);
	redLetters.resize(x);
	for (int i = 0; i < arr.size(); i++){
		arr[i].resize(y);
		redLetters[i].resize(y);
	}
	
	//fill each character into the matrix
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			char index;
			cin >> index; //read the character
			arr[i][j] = index; //assign the character to the correct index
		}
	}
	
	findStartingLetter(arr, redLetters, word, numberOfWords);
	printColoredLettersMatrix(arr, redLetters);
	
	return 0;
}