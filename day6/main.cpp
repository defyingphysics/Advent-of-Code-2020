// Day 5
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <set>


using namespace std;
// doskey run=g++ main.cpp -o main -std=c++17 $T main


bool parseFile(string fileName, vector<string>& input, vector<int>& numGroup)
{
	ifstream inputFile;
	inputFile.open(fileName);
	
	if (!inputFile.good()){
		cout << "inputFile: "<< fileName <<" not found" << endl;
		return false;
	}
	string line; 
	string answers = "";
	int i = 0;
	while(getline(inputFile, line))
	{	
		
		if (line == "" | inputFile.eof())
		{
			input.push_back(answers);
			numGroup.push_back(i);
			answers = "";
			i = 0;

		}
		else
		{
			answers.append(line);	
			i++;
		}
	} 	
	
	input.push_back(answers);
	numGroup.push_back(i);

	inputFile.close();	
	return true;
}


int main()
{
	int day = 10; 
	
	string inputFileName_example = "input_example.txt";
	string inputFileName_real = "input.txt";
	string inputFileName = ""; 
	int example = 0;
	vector<string> input; 
	
	cout  << endl;

	if (example){
		inputFileName = inputFileName_example;
	}
	else{
		inputFileName = inputFileName_real;
	}

	int sum1 = 0;
	int sum2 = 0;
	vector<int> numGroup;

	if(parseFile(inputFileName, input, numGroup))
	{
		for (int i = 0; i<input.size(); i++ )
		{
			set<char> ansSet (input[i].begin(), input[i].end());
			
			sum1 += ansSet.size();
			
			for (char c : ansSet)
			{
				 sum2 += (numGroup[i] == count(input[i].begin(), input[i].end(), c));
			}

		}			
	}
	cout << "Answer 1 - " <<  sum1 << "   Answer 2 - " << sum2;
}	