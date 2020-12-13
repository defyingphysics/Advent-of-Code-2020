// Example program
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main()
{
	//Part 1
	ifstream inputFile;
	inputFile.open ("day2.txt");
	string line; 
	int valid{0};

	if (inputFile.is_open())
	{		  
		while (getline(inputFile, line))
		{		
			istringstream ss(line);
			string password;
			int low{0}; 
			int high{0};
			char key; 
			char temp;
			ss >> low >> temp >>high >> key >> temp>> password;
			int count{0};
			// cout << low << " " << high << " " << key << " " << password << "\n";		
			
			for (char letter : password){
				if (letter == key){
					count ++;
				}
			}
			
			if ((count >= low) && (count <= high))
			{
				valid ++ ;	
			}
			
		 }	
		 
  }
  cout << valid << "\n" ; 
  inputFile.close();
  valid = 0;
  //Part 2 
  inputFile.open ("day2.txt");
  
  	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{	
			istringstream ss(line);
			string password;
			int low{0}; 
			int high{0};
			char key; 
			char temp;
			ss >> low >> temp >>high >> key >> temp>> password;
				
			if (password[low -1] == key)
			{
				if (password[high-1] != key){
					valid ++ ;	
				}
			}
			else if (password[high -1] == key)
			{
				if (password[low-1] != key){
					valid ++ ;	

				}
			}			
		}
	}
    cout << valid ; 
}
