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


	//cout << "Day 13 part a : " << PartA(lines) << endl;
	cout << "Day 13 part b : " << PartB(lines) << endl;

	return 0;
}


typedef unsigned long long int ulli;


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


ulli lcm(ulli n1, ulli n2)
{
	assert(n1 > 0);
	assert(n2 > 0);
	unsigned long long int max;
	//int lcmresult = 0;

	// maximum value between n1 and n2 is stored in max
	max = (n1 > n2) ? n1 : n2;
	assert(max > 0);
	do
	{
		if (max % n1 == 0 && max % n2 == 0)
		{
			//cout << "LCM = " << max;
			//lcmresult = max;
			break;
		}
		else
			++max;
	} while (true);

	return max;
}



enum class Method
{
	FirstBus,
	LargestBus,
	LCM
};

unsigned long long int PartB(vector<string>& lines)
{
	cout << "unsigned long long max = " << ULLONG_MAX << endl;
	cout << "unsigned long max = " << ULONG_MAX << endl;


	std::vector<std::string> buses;
	boost::split(buses, lines[1], [](char c) {return c == ','; });

	bool found = false;
	unsigned int max = 0;
	unsigned int maxloc = 0;
	std::vector<int> busesAsInts;
	ulli currLcm = 1;

	for (size_t idx = 0; idx < buses.size(); idx++)
	{
		string s = buses[idx];
		if (s[0] == 'x')
		{
			busesAsInts.push_back(-1);
			continue;
		}

		int busInt = stoi(s);
		if (busInt > max)
		{
			max = busInt;
			maxloc = idx;
		}

		ulli nextLcm = lcm(currLcm, busInt);
		assert(currLcm > 0);
		assert(nextLcm > 0);
		currLcm = nextLcm;
		busesAsInts.push_back(busInt);

	}


	Method method = Method::LCM;
	unsigned long long int baseTime;
	unsigned long long int increment;

	ulli startBig = (unsigned long long int)1e14;


	switch (method)
	{
	case Method::FirstBus:
	{
		baseTime = busesAsInts[0];
		//	cout << "100000000000000 % [0] =" << (startBig % busesAsInts[0]) << endl;
		// baseTime = startBig - (startBig % busesAsInts[0]);
		increment = busesAsInts[0];
		break;
	}


	case Method::LargestBus:
	{
		baseTime = max - maxloc;
		//baseTime = startBig - (startBig % max) - maxloc;
		increment = max;
		break;
	}

	case Method::LCM:
	{
		baseTime = currLcm;
		//baseTime = startBig - (startBig % max) - maxloc;
		increment = currLcm;
		break;
	}

	default:
	{
		cout << "Unknown method " << (int)method << endl;
		return -100;
	}
	}

	cout << " Starting at " << baseTime << ", incrementing by: " << increment << endl;
	unsigned long long int multiples = 0;
	size_t highestBus = 0;
	unsigned long long int loops = 0;

	while (!found && baseTime < ULLONG_MAX)
	{
		loops++;
		if ((baseTime / 1e10) > multiples)
		{
			multiples = (unsigned long long)(baseTime / 1e10) +1ULL;
			cout << " base time at " << baseTime << ", number of loops =" << loops << endl;
		}
		size_t i = 0;
		for (i = 0; i < busesAsInts.size(); i++)
		{
			if ((busesAsInts[i] < 1) || (((baseTime + i) % busesAsInts[i]) == 0))
			{
				found = true;
				if (i > highestBus)
				{
					//cout << "Changing increments to " << baseTime << endl;
					//increment = baseTime;
					highestBus = i;

					cout << " Found a match for all buses from 0 to " << i << ", time=" << baseTime << ", loops=" << loops << endl;
				}
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
			cout << " number of loops = " << loops << endl;
		}
		else
		{
			//cout << " found is false, i == " << i << endl;
			baseTime += increment;
		}

	}

	return baseTime;
}

