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
unsigned long long int PartB(vector<string>& lines);


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
	cout << " Number of paths = " << PartB(lines) << endl;
}


void PrepAdapters(const vector<string>& lines, vector<int>& adapterJolts)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		adapterJolts.push_back(stoi(lines[i]));
	}

	std::sort(adapterJolts.begin(), adapterJolts.end());
}


int PartA(vector<string>& lines)
{
	vector<int> adapterJolts;
	int result = -1;

	PrepAdapters(lines, adapterJolts);

	// one 3 Jolt step for the last adapter to device jump //
	int joltDiffs[5] = { 0,0,0,1,0 };
	int prevJolt = 0;

	for (size_t j = 0; j < adapterJolts.size(); j++)
	{
		int deltaJolt = adapterJolts[j] - prevJolt;
		cout << "Diff is: " << deltaJolt << endl;

		if (deltaJolt < 1 || deltaJolt > 4)
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

void PDepth(int depth)
{
	for (int d = 0; d < depth; d++)
		cout << "\t";

}

// returns the number of paths found
unsigned long long  int FindPaths(const vector<int>& adapterJolts, int startIndex, int startJolt, int targetJolt)
{
	unsigned long long int pathsHere = 0;

	static int depth = 1;
	
	
	//PDepth(depth);
	//cout << " i=" << startIndex << " start J=" << startJolt << endl;

	size_t i = startIndex;
	while (i < adapterJolts.size() && ((adapterJolts[i] - startJolt) <= 3))
	{
		//PDepth(depth);
		//cout << " current i=" << i << " J=" << adapterJolts[i] << endl;

		if (adapterJolts[i] != targetJolt)
		{
			depth++;
			pathsHere += FindPaths(adapterJolts, i + 1, adapterJolts[i], targetJolt);
			i++;
			depth--;
		}
		else
		{
			//PDepth(depth);
			//cout << " RETURNING 1 current i=" << i << " J=" << adapterJolts[i] << endl;
			return 1;
		}


	}

	//PDepth(depth);
	//cout << " returning 0, current i=" << i << ", path here=" << pathsHere <<  endl;
	return pathsHere;
}


unsigned long long int PartB(vector<string>& lines)
{
	vector<int> adapterJolts;
	unsigned long long int result = 0;

	PrepAdapters(lines, adapterJolts);

	int targetJolt = adapterJolts.back();
	int startJolt = 0;
	int startIndex = 0;

	result = FindPaths(adapterJolts, startIndex, startJolt, targetJolt);

	return result;

}
