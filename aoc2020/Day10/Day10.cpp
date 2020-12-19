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

	for (auto j : adapterJolts)
		cout << " " << j;
	cout << endl;
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
		//cout << "Diff is: " << deltaJolt << endl;

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


unsigned long long  int FindPathsDepth2Plus(const vector<int>& adapterJolts, int startIndex, int startJolt, int targetJolt)
{
	unsigned long long int pathsHere = 0;

	//cout << " FindPathsDepth2Plus() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << endl;


	size_t i = startIndex;
	while (i < adapterJolts.size() && ((adapterJolts[i] - startJolt) <= 3))
	{
		if (adapterJolts[i] != targetJolt)
		{
			i++;
			pathsHere += FindPathsDepth2Plus (adapterJolts, i, adapterJolts[i - 1], targetJolt);
		}
		else
		{
			return pathsHere + 1;
		}
	}

	return pathsHere;
}


#include <thread>
#include <future>

unsigned long long  int FindPathsDepth1 (const vector<int>& adapterJolts, int startIndex, int startJolt, int targetJolt)
{
	unsigned long long int pathsHere = 0;

	size_t i = startIndex;
	
	future <unsigned long long int>  f1, f2;
	bool doF1 = false;
	bool doF2 = false;


	cout << " FindPathsDepth1() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << endl;



	// up to 3 steps more
	size_t currIndex = startIndex + 2;
	if (currIndex < adapterJolts.size())
	{
		if (adapterJolts[currIndex] == targetJolt)
			pathsHere++;
		else if ((adapterJolts[currIndex] - startJolt) <= 3)
		{
			doF2 = true;
			f2 = std::async(FindPathsDepth2Plus, adapterJolts, currIndex + 1, adapterJolts[currIndex], targetJolt);
		}

	}

	currIndex = startIndex + 1;
	if (currIndex < adapterJolts.size())
	{
		if (adapterJolts[currIndex] == targetJolt)
			pathsHere++;
		else if ((adapterJolts[currIndex] - startJolt) <= 3)
		{
			f1 = std::async(FindPathsDepth2Plus, adapterJolts, currIndex + 1, adapterJolts[currIndex], targetJolt);
			doF1 = true;
		}

	}


	currIndex = startIndex;
	if (currIndex < adapterJolts.size())
	{
		if (adapterJolts[currIndex] == targetJolt)
			pathsHere++;
		else if ((adapterJolts[currIndex] - startJolt) <= 3)
			pathsHere += FindPathsDepth2Plus(adapterJolts, currIndex+1, adapterJolts[currIndex], targetJolt);
		cout << " FindPathsDepth1() Paths here after self loop == " << pathsHere << endl;

	}

	if (doF2) {
		pathsHere += f2.get();
		cout << " FindPathsDepth1() Paths here after f2 == " << pathsHere << endl;
	}
	if (doF1)
	{
		pathsHere += f1.get();
		cout << " FindPathsDepth1() Paths here after f1 == " << pathsHere << endl;
	}

	return pathsHere;
}


// returns the number of paths found
unsigned long long  int FindPaths(const vector<int>& adapterJolts, int startIndex, int startJolt, int targetJolt)
{
	unsigned long long int pathsHere = 0;


	size_t i = startIndex;

	future <unsigned long long int>  f1, f2;
	bool doF1 = false, doF2 = false;


	cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << endl;

	// up to 3 steps more
	size_t currIndex = startIndex + 2;
	if (currIndex < adapterJolts.size())
	{
		if (adapterJolts[currIndex] == targetJolt)
			pathsHere++;
		else if ((adapterJolts[currIndex] - startJolt) <= 3)
		{
			doF2 = true;
			f2 = std::async(FindPathsDepth1, adapterJolts, currIndex + 1, adapterJolts[currIndex], targetJolt);
		}

	}

	currIndex = startIndex + 1;
	if (currIndex < adapterJolts.size())
	{
		if (adapterJolts[currIndex] == targetJolt)
			pathsHere++;
		else if ((adapterJolts[currIndex] - startJolt) <= 3)
		{
			doF1 = true;
			f1 = std::async(FindPathsDepth1, adapterJolts, currIndex + 1, adapterJolts[currIndex], targetJolt);
		}

	}


	currIndex = startIndex;
	if (currIndex < adapterJolts.size())
	{
		if (adapterJolts[currIndex] == targetJolt)
			pathsHere++;
		else if ((adapterJolts[currIndex] - startJolt) <= 3)
			pathsHere += FindPathsDepth1(adapterJolts, currIndex+1, adapterJolts[currIndex], targetJolt);

		cout << " FindPaths() Paths here after self loop == " << pathsHere << endl;
	}

	if (doF2)
	{
		pathsHere += f2.get();
		cout << " FindPaths() Paths here after f2 == " << pathsHere << endl;
	}

	if (doF1)
	{
		pathsHere += f1.get();
		cout << " FindPaths() Paths here after f1 == " << pathsHere << endl;
	}
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
