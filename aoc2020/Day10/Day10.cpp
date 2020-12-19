// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>    // std::sort

#include "FileLoad.h"

using namespace std;


int PartA(vector<string>& lines);
int PartB(vector<string>& lines);


int main(int argc, char** argv)
{
	std::cout << "Hello World!\n";


	ShowInputs(argc, argv);

	if (argc != 2)
		return -2;

	vector<string> lines;
	if (!OpenAndReadInput(argv[1], lines))
	{
		return -1;
	}

	cout << " Number of 1 jolts steps * Number of 3 jolt steps = " << PartA(lines) << endl;
}

int PartA(vector<string>& lines)
{
	vector<int> adapterJolts;
	int result = -1;

	for (size_t i = 0; i < lines.size(); i++)
	{
		adapterJolts.push_back(stoi(lines[i]));
	}

	std::sort(adapterJolts.begin(), adapterJolts.end());

	// one 3 Jolt step for the last adapter to device jump //
	int joltDiffs[5] = { 0,0,0,1,0 };
	int prevJolt = 0;

	for (size_t j = 0; j < adapterJolts.size(); j++)
	{
		int deltaJolt = adapterJolts[j] - prevJolt;
		cout << "Diff is: " << deltaJolt << endl;

		if (deltaJolt < 0 || deltaJolt > 4)
		{
			cout << "^^^ INVALID JOLT ****************************" << endl;
			continue;
		}
		joltDiffs[deltaJolt]++;
		prevJolt = adapterJolts[j];
	}

	result = joltDiffs[1] * joltDiffs[3];

	return result;
}


int PartB(vector<string>& lines)
{
	return -1;
}
