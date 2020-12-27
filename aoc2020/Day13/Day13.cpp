// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <string>


//#include <boost/algorithm>
#include <boost/algorithm/string.hpp> 


#include "FileLoad.h"

using namespace std;


int PartA(vector<string>& lines);
int PartB(vector<string>& lines);


int main(int argc, char** argv)
{
	ShowInputs(argc, argv);

	if (argc != 2)
	{
		cout << "Invalid number of args : " << argc << endl;
		return -2;
	}

	vector<string> lines;
	if (!OpenAndReadInput(argv[1], lines))
	{
		cout << "Opening and reading file failed." << endl;
		return -1;
	}

	if (lines.size() != 2)
	{
		cout << "Expected exactly 2 lines, instead found=" << lines.size() << endl;
		return -3;
	}


	cout << "Day 13 part a : " << PartA(lines) << endl;
	cout << "Day 13 part b : " << PartB(lines) << endl;

	return 0;
}


int PartA(vector<string>& lines)
{
	std::vector<std::string> buses;
	boost::split(buses, lines[1], [](char c) {return c == ','; });


	int currTime = stoi(lines[0]);
	cout << "Start time = " << currTime << endl;
	cout << "Bus line: " << lines[1] << endl;

	int soonestTime = LONG_MAX;
	int bestBus = -1;

	for (auto bus : buses)
	{
		//cout << " bus? " << bus << endl;

		if (bus == "x")
			continue;

		int busId = stoi(bus);
		//cout << "Current bus id = " << busId << endl;

		int nextArrival = 0;
		while (nextArrival < currTime)
		{
			nextArrival += busId;
		}
		if (nextArrival < soonestTime)
		{
			soonestTime = nextArrival;
			bestBus = busId;
		}
	}

	cout << "Soonest bus " << bestBus << " @ " << soonestTime << endl;
	int waitTime = soonestTime - currTime;
	return bestBus * waitTime;
}

int PartB(vector<string>& lines)
{
	return -2;
}

