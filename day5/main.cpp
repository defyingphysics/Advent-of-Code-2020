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
using namespace std;
// doskey run=g++ main.cpp -o main -std=c++17 $T main



struct Ticket
{
	string upDown; 
	string leftRight;
	Ticket(string uD, string lR) : upDown(uD), leftRight(lR){}
};

class TicketSim
{
	typedef int seatID;
	vector<Ticket> tickets; 
	int numRows = 127; 
	int numCols = 7; 
	vector<int> range; 
	
	int search(string str, vector<int> range, int val = 0)
	{
		while(str.size() != 1)
		{
			//lower
			if ((str[0] == 'F' ) | (str[0] == 'L'))
				range[1] = range[0] + (range[1] - range[0])/2;
			//upper
			else
				range[0] = ( range[0]+ ((range[1] - range[0])+1)/2);				
			str.erase(0,1);
			return search(str, range, val);
		} 
		return ((str[0] == 'F' ) | (str[0] == 'L')) ? range[0]:range[1];
	}
	
	
	int getSeatID(Ticket ticket);
	
public:	
	TicketSim(vector<Ticket> input): tickets(input){}
	int getMaxTicket ();
	void printTickets (); 
	int getMyTicket ();
	

};

void TicketSim::printTickets()
{
	cout<< "Tickets are: " << endl;
	for (auto ticket: tickets)
	{
		cout << "U-D: " << ticket.upDown << " and L-R: " << ticket.leftRight << endl;
	}
	
}

int TicketSim::getSeatID(Ticket ticket)
{
	range = {0,numRows};
	int row  = search(ticket.upDown, range);

	range = {0,numCols};
	int column = search(ticket.leftRight, range);
	
	return (row*8) + column;	
}

int TicketSim::getMaxTicket ()
{
	int max = 0; 
	for (auto ticket : tickets)
	{
		int seatId = getSeatID(ticket);
		max =  seatId > max ? seatId : max;
		// cout << "SeatID: " << seatId << endl;
	}
	
	return max;
}

int TicketSim::getMyTicket()
{
	vector <seatID> seatIds;
	for (auto ticket : tickets)
	{
		seatIds.push_back(getSeatID(ticket));
	}
	
	sort(seatIds.begin(), seatIds.end());
	if(!seatIds.empty())
	{
		for (auto it = seatIds.begin(); it != seatIds.end(); ++it)
		{
			if ((*(it+1) - *it) == 2)
				return *it + 1;
		}
	}
	else
		return -2;

	return 1;
}


bool parseFile(string fileName, vector<Ticket>& input)
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
		getline(inputFile, line);
		if(!line.empty())
		input.push_back(Ticket(line.substr(0,7),line.substr(7)));	
	} 	
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
	vector<Ticket> input; 
	
	cout  << endl;

	if (example){
		inputFileName = inputFileName_example;
	}
	else{
		inputFileName = inputFileName_real;
	}
	
	if(parseFile(inputFileName, input))
	{
		TicketSim ticketSim(input);
		// ticketSim.printTickets();
		cout << "Answer 1 " << ticketSim.getMaxTicket() << endl;
		
		cout << "Answer 2 " << ticketSim.getMyTicket() << endl;
			
	}
}	