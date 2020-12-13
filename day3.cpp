// Example program
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


int main()
{
	//Part 1
	ifstream inputFile;
	inputFile.open ("day3.txt");
	string line; 
	int numRow {323}; 
	int numCol {31};
	int right[5] {1,3,5,7,1};
	int down[5] {1,1,1,1,2};	
	char map [numRow][numCol];
	int row = 0;
	
	while(getline(inputFile,line)) //get one line from the file
	{	
		istringstream ss (line); 
		int column = 0;
		while(ss.good())
		{
			ss >> map[row][column];
			column ++;
		}
		row++;
	}	
	
	int treeCount = 0;
	double sum{1};
	
	for (int k = 0 ; k < 5 ; k++)
	{
		for (int i = 0; i < numRow; i+=down[k] )
		{
			int horizontalPos = ((i/down[k])*right[k]);
			horizontalPos = horizontalPos% numCol;		
			
			 if (map[i][horizontalPos] == '#')
			 {
				treeCount++;
			 }
		}	
		cout << treeCount << endl;
		sum = sum * treeCount;
		treeCount = 0;
	}

	cout << std::setprecision (15) <<sum << endl;	
}		