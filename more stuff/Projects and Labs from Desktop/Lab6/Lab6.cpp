/*******************************
 * Programmer: Ryan Strenkowski
 * Instructor: Dr. Mao
 * Course: CSC230-03
 * Lab6
 ******************************/ 

#include <iostream>
#include <stdlib.h>
using namespace std;

int A[10];

void com(int len, int size)
{
  if(len < 1)
    {
      for(int i = size; i > 0; i--)
      {
	    cout << A[i-1];
	  }
	  cout << endl;
    }

  else
    {
      for(int i = 0; i <= 9; i++)
	  {
	    A[len-1] = i;
	    com(len - 1, size);
	  }
    } 
}

int main(int argc, char* argv[])
{
  com(atoi(argv[1]), atoi(argv[2]));
}
