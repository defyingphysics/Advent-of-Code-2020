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

// doskey run1=g++ day10.cpp -o day101 -std=c++17 $T day101
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

int delve(int& sum, int& key, int& oldKey, map<int,vector<int>>& tree, map<int,int>& nodeIncrementStatic, map<int,int>& nodeIncrementDynamic, int& split, bool& print,map<int,int>& treeSaver,map<int,int>& nodePruned, vector<int>& splits, vector<int>& valSincesplit, vector<int>& thisChain )
{

	thisChain.push_back(key);

	if (nodeIncrementStatic[split] == -1)
	{
		cout << "MINUS 1";
		return false;
	}
	
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
	
		// cout << print << endl;
		if (print)		{
			cout << key << ">" ;
			cout << "split" << split <<endl;

		}
		
		
		if ((nodeIncrementStatic[key] > 0) & (nodePruned[key] != 1))
		{
			// cout << "Old Split " << oldSplit << " NewSplit" << newSplit << endl; 	
			treeSaver[key]++;
			cout << "SplitAdder - Adding treeSaver : " << key << " value: " << 1 << " new " << treeSaver[key] << endl;
			splits.push_back(key);
		}
		
		if (nodePruned[key] == 1){
			//if reached a pruned node and there was no split, you must have pruned the whole tree so return and end.
			cout << "Reached pruned: " << key << endl;
			
			// cout << "Add: " << split << "Amount:  "<< treeSaver[key] << " New value" << treeSaver[split]<<endl;
			cout << "Adding Sum : " << treeSaver[key] << endl;
			sum += treeSaver[key];
			
			// treeSaver[split] +=treeSaver[key];
			// cout << "Adding to treeSaver : " << split << " value: " << treeSaver[key] << "new " << treeSaver[split] << endl;

			// treeSaver[split] -= 1;			
			cout << "Fix Previous since we have reached a pruned " <<  key << " - " <<treeSaver [key] <<endl;
			for (auto val : splits)
			{
				treeSaver[val] = treeSaver[val] - 1 + treeSaver [key];
				cout << "Adding to treeSaver : " << val << " value: " << treeSaver[key] << "-1 : new " << treeSaver[val] << endl;

			}
			
			
			if (split == 0)
			{
						cout << "SPLIT 0";

				// return false;
			}
			nodeIncrementDynamic[split] -= 1;

			cout << "Key: " << key << endl;
			return true;
		}
		split = nodeIncrementDynamic[key] > 0 ? key : split;
		
		// cout << key  << " -> "<<tree[key][nodeIncrementDynamic[key]]<< endl;

		return delve (sum,tree[key][nodeIncrementDynamic[key]],key, tree,nodeIncrementStatic, nodeIncrementDynamic, split, print,treeSaver,nodePruned, splits,valSincesplit,thisChain);
		
	}
	else{
		
		if (split == 0)
		{
			return false;
		}
		
		// decrement the split and reset everything below it. 
		nodeIncrementDynamic[split] -= 1;
						
		for( auto& [key, val] : nodeIncrementDynamic)
		{
			if (key > split)
			{
				nodeIncrementDynamic[key] = nodeIncrementStatic[key];
			}
		}
		
		if (print)		{
			cout << " ---- end ----- " << split <<endl;
		}
		
		
					// cout << "Old Split " << oldSplit << " NewSplit" << newSplit << endl; 	
 
		
		for (auto node : valSincesplit)
		{
			nodePruned[node] = 1;
			treeSaver[node]++;
			cout << "Pruned: " << node << "with value" << treeSaver[node] <<endl;		
		}
		
		// treeSaver[split] ++;
		// cout << "Adding treeSaver : " << split << " value: " << 1 << " - new " << treeSaver[split] << endl;

		sum += 1;
		cout << "Return True" << endl;
		return true;
	}
}


bool IsZero(int i) {
    return i == 0;
}

int getNumberComb(vector<int> input)
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
	
		//Print
		cout << *it << " - ";
		for (auto entry : val)
		{
			cout << entry<< ", ";
		}
		cout << endl;

	}

	map<int,int> nodeIncrementStatic; 	

	//For increment add how many paths for each key. 
	for (auto& [key, val] : tree)
	{
		nodeIncrementStatic[key] = val.size()-1;
	}
	
	map<int,int> treeSaver; 	
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

	int sum = 0;
	int split = 0;
	bool print = 1; 
	int printCount =0; 
	int localSplitOldOld = 0; 
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

		cout<< "_____________________________________________"<< endl;
		cout<< "Sum Before" << sum << endl;

		string temp;
		// cin >>temp;
		int newAdd = delve(sum,currKey,oldKey, tree,nodeIncrementStatic, nodeIncrementDynamic, split,print, treeSaver, nodePruned, splits,valSincesplit,thisChain);

		cout<< "Sum After" << sum << endl;

		if (!newAdd)
		{
			break;
		}

		localSplitNew = split; 

		cout << "  localSplitNew " << localSplitNew << "  localSplitOld  " << localSplitOld <<endl;

		
		if (localSplitNew < localSplitOld)
		{


			 // treeSaver[localSplitOld]++;
			 // cout << "Add value of: "<< 1 << " To: "<< localSplitOld << " New value" << treeSaver[localSplitOld]<<endl;


			cout << "Fix up the rest" << endl;
		
			vector<int> toCleanKey = {};
			vector<int> toCleanVal = {};
		
			for( auto& key : thisChain)
			{	
				if (key > split)
				{
						toCleanKey.push_back(key);
						toCleanVal.push_back(treeSaver[key]);
				}
			}
		
				cout << endl;	
			int index =0;

			for (auto key : toCleanKey)
			{
				cout << "Node: " << key << "with value" << toCleanVal[index] << " Pruned: "<< nodePruned[key] <<  endl;		
				index++;
			}
			cout << endl;	
			index =0;
			for( auto& key : toCleanKey)
			{
				if (nodePruned[key] != 1)
				{
					if (treeSaver[key] ==0)
					{
						auto it = find_if_not(toCleanVal.begin()+index, toCleanVal.end(), IsZero);	
						
						treeSaver[key] = *it;
						// cout << "ZERO IS " << *it << endl;
						
					}
				}

				
				if (nodeIncrementDynamic[key] == 0 )
				{
					nodePruned[key] = 1;
					// treeSaver[key] = hack.back();
					cout << "Pruned: " << key << "with value" << treeSaver[key] <<endl;
				}
				nodeIncrementDynamic[key] = nodeIncrementStatic[key];
				index ++;
			}	
			
									nodePruned[localSplitOld] = 1;
			cout << "Pruned: " << localSplitOld << "with value" << treeSaver[localSplitOld] <<endl;
			
		}
		localSplitOld = localSplitNew;
		localSplitOldOld = localSplitOld;

		// printCount++;
		// if (printCount == 100){
			// cout << endl; 
			// print = true;
			// printCount = 0;
		// }
		// else{
			// print = false;
		// }
		 split = 0;
	}
	// for (int i =0; i< 19209; i++)
	// {
		// delve(input.front(), tree,nodeIncrementStatic, nodeIncrementDynamic, split);
	// }
	return sum;
}

int main()
{
	int day = 10; 
	
	string inputFileName_example = "day"+to_string(day)+"_example.txt";
	string inputFileName_real = "day"+to_string(day)+".txt";
	string inputFileName = ""; 
	int example = 1;
	int numValid = 0;
	
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
		
		int answer2 = getNumberComb(input);
		
		cout << "Answer 2 = " << answer2 <<endl;

	}
	
	
	
}	