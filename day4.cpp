// Example program
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class passPort
{
private:
	int height{-1};
	string heightUnits{-1};

	int birthYear{-1};
	int issueyear{-1}; 
	int expirationYear{-1}; 
	string hairCol{"-1"}; 
	string eyeCol{"-1"}; 
	string passportId{-1}; 
	int countryId{-1};
	
	vector<string> validEye{"amb","blu","brn","gry","grn","hzl","oth"}; 

    const char delim = ' ';
    const char delimKey = ':';

public:
	bool checkValid();
	void addValues(string attributes);
	void printPassport();


};

bool passPort::checkValid()
{
	if((birthYear == -1) | (birthYear < 1920) | (birthYear > 2002)){
		// cout << "birthYear" << birthYear << endl;
		return false;
	}
	if( (height == -1)  | (heightUnits != "in" & heightUnits != "cm")){
		// cout << "height" <<height << endl;
		// cout << "heightUnits" <<heightUnits << endl;
		return false;
	}
	if (heightUnits == "cm" & (height < 150 | height > 193) ){
				// cout << "height" <<height << endl;
		return false;
	}
	if (heightUnits == "in" & (height < 59 | height > 76)){
				// cout << "height" <<height << endl;
		return false;
	}
	
	if((issueyear == -1) | (issueyear < 2010) | (issueyear > 2020)){
		return false;
	}
	if((expirationYear == -1) | (expirationYear < 2020) | (expirationYear > 2030)){
						// cout << "expirationYear" <<expirationYear << endl;
		return false;
	}
	if((passportId == "-1") | (passportId.size() != 9)){

		return false;
	}
	if(countryId == -1){
		// return false;
	}
	if(hairCol == "-1" | (hairCol[0] != '#') | hairCol.size() != 7){
						// cout << "hairCol" <<hairCol << endl;
		return false;
	}
	if((eyeCol == "-1") | (find(validEye.begin(), validEye.end(), eyeCol) == validEye.end())){

		return false;
	}
					cout << "passportId" <<passportId << endl;

	return true;
}

void passPort::printPassport()
{
	cout << "height " <<height  << " birthYear " <<birthYear  << " issueyear " <<issueyear  << " expirationYear" <<expirationYear  << 
	" hairCol" << hairCol << " eyeCol " << eyeCol << " passportId" <<passportId  << " countryId " << countryId << endl;
}

void passPort::addValues(string attributes)
{
	stringstream ss1(attributes);
	string attribute;
	string key; 
	string val;
	string temp;
	
	while(getline(ss1, attribute, delim))
	{
		stringstream ss2(attribute);
		getline(ss2, key, delimKey);
		getline(ss2, val, delimKey );
		stringstream ss3(val); 

		if(key == "byr"){
			ss3 >> birthYear;
		}
		else if(key == "iyr"){
			ss3 >> issueyear;
					}
		else if(key == "eyr"){
			ss3 >> expirationYear;			
		}
		 if(key == "hgt"){
			ss3 >> height >> heightUnits;
		}
		else if(key == "hcl"){
			ss3 >> hairCol;			
		}
		else if(key == "ecl"){
			ss3 >> eyeCol;
		}
		else if(key == "pid"){
			ss3 >> passportId;
		}
		else if(key == "cid"){
			ss3 >> countryId;
		}
	}
}

bool parseFile(string fileName, vector<passPort*>& travellers)
{
	ifstream inputFile;
	inputFile.open(fileName);
	
	if (!inputFile.good()){
		cout << "inputFile: "<< fileName <<" not found" << endl;
		return false;
	}
	string line; 
	
	while(!inputFile.eof())
	{	
	string travAttributes;
		while (!inputFile.eof())
		{	
			passPort* traveller = new passPort; 
			getline(inputFile,line);
			travAttributes += line;
			travAttributes += " ";

			if (line.empty() | inputFile.eof()){
				traveller->addValues(travAttributes);
				travellers.push_back(traveller);
				travAttributes = "";
			}	
		}
	} 	
	inputFile.close();	
	return true;
}


int main()
{
	int day = 4; 
	
	string inputFileName_example = "day"+to_string(day)+"_example.txt";
	string inputFileName_real = "day"+to_string(day)+".txt";
	string inputFileName = ""; 
	int example = 0;
	int numValid = 0;
	
	
	if (example){
		inputFileName = inputFileName_example;
	}
	else{
		inputFileName = inputFileName_real;
	}
		
	std::vector<passPort*> travellers; 
	
	if(parseFile(inputFileName, travellers))
	{
		for (auto traveller : travellers)
			{
				numValid += traveller->checkValid();	
			}
			
			cout << "_______________________________________" << endl;
			cout << numValid << endl;
	}
	
	
	
}	