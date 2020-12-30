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
unsigned long long int PartB(vector<string>& lines);


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

unsigned long long int PartB(vector<string>& lines)
{
	cout << "unsigned long long max = " << ULLONG_MAX << endl;
	cout << "unsigned long max = " << ULONG_MAX << endl;

	std::vector<std::string> buses;
	boost::split(buses, lines[1], [](char c) {return c == ','; });

	bool found = false;
	int max = -1;
	std::vector<int> busesAsInts;

	for (auto s : buses)
	{
		if (s[0] == 'x')
		{
			busesAsInts.push_back(-1);
			continue;
		}

		int busInt = stoi(s);
		if (busInt > max)
			max = busInt;

		busesAsInts.push_back(busInt);

	}

	unsigned long long int baseTime = 0;

	while (!found && baseTime < ULONG_MAX)
	{
		size_t i = 0;
		for (i = 0; i < busesAsInts.size(); i++)
		{
			if ((busesAsInts[i] < 1) || (((baseTime + i) % busesAsInts[i]) == 0))
			{
				found = true;

			}
			else
			{
				found = false;
				break;
			}

		}

		if (found)
		{
			cout << " found is true, i == size? " << (i == busesAsInts.size()) << endl;
		}
		else
		{
			//cout << " found is false, i == " << i << endl;
			baseTime += busesAsInts[0];
		}

	}

	return baseTime;
}

