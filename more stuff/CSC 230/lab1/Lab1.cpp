#include <iostream>
using namespace std;

int main(){
	int x;
	int y;
	
	cin >> x; //get the amount of columns
	cin >> y; //get the amount of rows
	
	char arr [x][y]; //create a 5x5 matrix
	
	//fill each character into the matrix
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			char index;
			cin >> index; //read the character
			arr[i][j] = index; //assign the character to the correct index
		}
	}
	
	//print out the matrix
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	return 0; //exit
}