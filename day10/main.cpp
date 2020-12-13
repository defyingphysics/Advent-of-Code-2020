// Example program
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
// doskey run=g++ main.cpp -o main -std=c++17 $T main

bool parseFile(string fileName, vector<int>& input)
{
	ifstream inputFile;
	inputFile.open(fileName);
	
	if (!inputFile.good()){
		cout << "inputFile: "<< fileName <<" not found" << endl;
		return false;
	}
	string line; 
	
		input.push_back(0);

	while(!inputFile.eof())
	{	
		getline(inputFile, line);
		istringstream ss(line);
		int val; 
		ss >> val;
		input.push_back(val);
	} 	
	inputFile.close();	
	return true;
}

void getComb(vector<int> input, int& diff_1, int& diff_3)
{
	int current = 0; 
	vector<int>::iterator it = input.begin();
	
	while (it != input.end())
	{
		if ((*(next(it,1)) - *it) > 3){
			break;
		}
		diff_1 = ((*(next(it,1)) - *it) == 1) ? ++diff_1 : diff_1;
		diff_3 = ((*(next(it,1)) - *it) == 3) ? ++diff_3 : diff_3;				
		it++;
	}
}

int delve(long long int& sum, int& key, map<int,vector<int>>& tree, map<int,int>& nodeIncrementStatic, map<int,int>& nodeIncrementDynamic, int& split,map<int,long long int>& treeSaver,map<int,int>& nodePruned, vector<int>& splits, vector<int>& valSincesplit, vector<int>& thisChain )
{
	thisChain.push_back(key);	
	
	if ((nodeIncrementDynamic[key] > 0))
	{
		valSincesplit = {};		
	}
	else 
	{
		valSincesplit.push_back(key);
	}
	

	if (!tree[key].empty())
	{
		if ((nodeIncrementStatic[key] > 0) & (nodePruned[key] != 1))
		{
			treeSaver[key]++;
			splits.push_back(key);
		}
		
		if (nodePruned[key] == 1){
			
			sum += treeSaver[key];
				
			//Fix Previous since we have reached a pruned
			for (auto val : splits)
			{
				treeSaver[val] = treeSaver[val] - 1 + treeSaver [key];
			}
			nodeIncrementDynamic[split] -= 1;
			return true;
		}
		split = nodeIncrementDynamic[key] > 0 ? key : split;

		return delve (sum,tree[key][nodeIncrementDynamic[key]], tree,nodeIncrementStatic, nodeIncrementDynamic, split, treeSaver,nodePruned, splits,valSincesplit,thisChain);
		
	}
	else{
		
		if (split == 0)
			return false;
		
		// decrement the split and reset everything below it. 
		nodeIncrementDynamic[split] -= 1;
						
		for( auto& [key, val] : nodeIncrementDynamic)
		{
			if (key > split)
				nodeIncrementDynamic[key] = nodeIncrementStatic[key];

		}
		for (auto node : valSincesplit)
		{
			nodePruned[node] = 1;
			treeSaver[node]++;
		}
		sum += 1;
		return true;
	}
}

bool IsZero(int i) {
    return i == 0;
}

long long int getNumberComb(vector<int> input)
{
	map<int,vector<int>> tree; 

	//empty map with input as keys   
	for (int val : input)
	{
		tree[val] = vector<int>();
	}
	// for tree each key add possible options
	for (auto& [key, val] : tree)
	{
		vector<int>::iterator it = find(input.begin(), input.end(), key);
		for (int i = 1; i <= 3; i++)
		{
			int difference = *(next(it,i)) - *it;
			if( (difference==1) | (difference==2) | (difference==3))
			{
				val.push_back(*(next(it,i)));
			}
		}
	}

	map<int,int> nodeIncrementStatic; 	

	//For increment add how many paths for each key. 
	for (auto& [key, val] : tree)
	{
		nodeIncrementStatic[key] = val.size()-1;
	}
	
	map<int,long long int> treeSaver; 	
	for (auto& [key, val] : tree)
	{
		treeSaver[key] = 0;
	}
	map<int,int> nodePruned; 	
	for (auto& [key, val] : tree)
	{
		nodePruned[key] = 0;
	}
	
	map<int,int> nodeIncrementDynamic = nodeIncrementStatic; 	

	long long int sum = 0;
	int split = 0;
	int localSplitOld = 0; 
	int localSplitNew = 0; 
	int saverSum = 0;
	int currKey = input.front();
	int oldKey= input.front();

	//Loop through map and sum possible paths
	while (1)
	{
		vector<int> splits = {};
		vector<int> valSincesplit = {};
		vector<int> thisChain = {};
		
		//iterate one delve
		if (!(delve(sum,currKey, tree,nodeIncrementStatic, nodeIncrementDynamic, split,treeSaver, nodePruned, splits,valSincesplit,thisChain)))
			break;

		localSplitNew = split; 

		if (localSplitNew < localSplitOld)
		{
			//Need to prune
			vector<int> toCleanKey = {};
			vector<long long int> toCleanVal = {};
		
			for( auto& key : thisChain)
			{	
				if (key > split)
				{
					toCleanKey.push_back(key);
					toCleanVal.push_back(treeSaver[key]);
				}
			}
		
			int index =0;
			for( auto& key : toCleanKey)
			{
				if (nodePruned[key] != 1 && treeSaver[key] ==0)
				{
					auto it = find_if_not(toCleanVal.begin()+index, toCleanVal.end(), IsZero);	
					treeSaver[key] = *it;				
				}

				if (nodeIncrementDynamic[key] == 0 )
					nodePruned[key] = 1;
				
				nodeIncrementDynamic[key] = nodeIncrementStatic[key];
				index ++;
			}		
			nodePruned[localSplitOld] = 1;		
		}
		localSplitOld = localSplitNew;
		split = 0;
	}
	return sum;
}

int main()
{
	int day = 10; 
	
	string inputFileName_example = "input_example.txt";
	string inputFileName_real = "input.txt";
	string inputFileName = ""; 
	int example = 0;
	
	cout  << endl;

	if (example){
		inputFileName = inputFileName_example;
	}
	else{
		inputFileName = inputFileName_real;
	}
	
	int diff_1 = 0; 
	int diff_3 = 0; 
		
	vector<int> input; 
	vector<vector<int>> allComb;

	if(parseFile(inputFileName, input))
	{
		sort(input.begin(), input.end());
		input.push_back(input.back() + 3);
	
		getComb(input, diff_1, diff_3);	
		int answer = diff_1 * diff_3;
		cout << "Answer1 = "<< diff_1 <<"*" << diff_3  << " = "<< answer <<endl;
		
		long long int answer2 = getNumberComb(input);
		cout << "Answer 2 = " << answer2 <<endl;
	}
}	