// Example program
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	
  ifstream inputFile;
  inputFile.open ("day1.txt");
  
  int num1 = 0; 
  int num2 = 0;
  int numLines = 200;   
  int inArray[numLines]; 
   if (inputFile.is_open())
  {
	  int count = 0 ;
	  for (int count = 0; count <= numLines; count ++  )
	  {
		inputFile >> inArray[count];  
	  }
		
  }
  inputFile.close();
     
	 
	 // for (int temp : inArray){
		 
		 // cout << temp << "\n";
	 // }
	 
   
   for (int i=0 ; i < 200; i++)
	{	
		for (int j=i ; j < 200; j++)
		{
			for (int k=j ; k < 200; k++)
			{
				int sum = inArray[j]+inArray[i]+inArray[k]; 
				if (sum == 2020){	
				cout <<inArray[j]*inArray[i]* inArray[k];
				}
			}	
		}
	}
	
   
   
   
}
