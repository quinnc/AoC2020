// Day15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

//#include <boost/algorithm>
#include <boost/algorithm/string.hpp> 


#include "FileLoad.h"

using namespace std;



ulli PartA(vector<string>& lines);
ulli PartB(vector<string>& lines);


int main(int argc, char** argv)
{
	string name = argv[0];

	name = name.substr(name.find_last_of('\\') + 1);

	cout << endl << "--- Rambuctious Recittation ---" << endl << endl;

	cout << " int max = " << std::hex << std::numeric_limits<int>::max() << endl;
	cout << " ulli max = " << std::hex << std::numeric_limits<ulli>::max() << endl;
	cout << std::dec;

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


	if (lines.size() != 1)
	{
		cout << " Expected 1 line, found " << lines.size() << endl;
		return -1;
	}

	cout << "---> ABout to call Part A <----" << endl;
	ulli partAout = PartA(lines);
	cout << "---> Returned from Part A <----" << endl;
	cout << name << " part a : " << partAout << endl;

	cout << endl;

	cout << "---> About to call Part B <----" << endl;
	ulli partBout = PartB(lines);
	cout << "---> Returned from Part B <----" << endl;
	cout << name << " part b : 0x" << std::hex << partBout << std::dec << " == " << partBout << endl;

	return 0;
}


#define MAX_MAPS 10

ulli PlayGame(vector<string>& lines, int totalSteps)
{
	// map of number to the last turn number it was spoken
	//unordered_map<int, int> trackMapArray[MAX_MAPS+1];
	map<int, int> trackMap;

	int step = 0;

	vector<string> inputNumbers;

	boost::split(inputNumbers, lines[0], [](char c) {return c == ','; });

	for (const auto& numStr : inputNumbers)
	{
		int n = stoi(numStr);
		//trackMapArray[0][n] = step;
		trackMap[n] = step;
		step++;
	}

	bool lastNumberFirstTime = true;
	int delta = -1;
	int next = -1;

	while (step < totalSteps)
	{
		if (lastNumberFirstTime)
		{
			next = 0;
		}
		else
		{
			next = delta;
		}

		int index = next / 1000000;
		if (index > MAX_MAPS)
			index = MAX_MAPS;

		//unordered_map<int, int>& trackMap = trackMapArray[index];

		if (trackMap.find(next) == trackMap.end())
		{
			lastNumberFirstTime = true;
			delta = -1;
		}
		else
		{
			lastNumberFirstTime = false;
			delta = step - trackMap[next];
		}

		trackMap[next] = step;
		//cout << "  Round " << step << " -- current number spoken=" << next << ", was this the first time? " << lastNumberFirstTime << ", delta? " << delta << endl;
		step++;
	}

	cout << "  Round " << step-1 << " -- current number spoken=" << next << ", was this the first time? " << lastNumberFirstTime << ", delta? " << delta << endl;
	return next;
}



ulli PartA(vector<string>& lines)
{

	return PlayGame(lines, 2020);
}

ulli PartB(vector<string>& lines)
{

	return PlayGame(lines, 30000000);
}