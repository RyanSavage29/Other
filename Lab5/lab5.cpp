#include <iostream>
#include <stdlib.h>
using namespace std;

int A[100];

void com(int n, int t)
{
  if(n >= 1)
    {
      for(int i = 0; i < 10; i++)
	{
	  A[n-1] = i;
	  com(n-1,t);
	}
    }
  else
    {
      for(int i = 0; i < t; i++)
	{
	  cout << A[i];
	}
      cout << endl;
    } 
}

int main(int argc, char* argv[])
{
  int l = atoi(argv[1]);
  com(l, l);
  return 0;
}
