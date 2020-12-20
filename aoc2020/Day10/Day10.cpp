// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>    // std::sort
#include <map>
#include <mutex>

#include <thread>
#include <future>


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

struct DepthResults
{

	unsigned long long int paths = 0;
	size_t index = -1;
	bool inProgress = false;
	mutex mtx;
};

mutex mapmtx;
map<size_t, DepthResults*> results;

// returns the number of paths found
unsigned long long  int FindPaths(const vector<int>& adapterJolts, int startIndex, int startJolt, int targetJolt)
{
	unsigned long long int pathsHere = 0;
	size_t i = startIndex;

	const int MAX = 3;
	future <unsigned long long int>  f[MAX];
	bool doF[MAX] = { false, false, false };



	cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << endl;

	if (adapterJolts[startIndex] == targetJolt)
		return 1;


	DepthResults* dr = new DepthResults();
	mapmtx.lock();
	auto currResults = results.find(startIndex);
	if (currResults != results.end())
	{

		cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << ".  Found entry, waiting for results..." << endl;

		mapmtx.unlock();

		if (currResults->second->inProgress)
		{
			// wait here for the results
			currResults->second->mtx.lock();


			currResults->second->mtx.unlock();
		}

		if (currResults->second->inProgress || (currResults->second->paths == 0))
			cout << " STILL IN PROGRESS! or paths = 0 WHAT? " << currResults->second->index << endl;


		cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << ". Waiting complete: paths = " << currResults->second->paths << endl;

		return currResults->second->paths;
	}


	//cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << ". Starting calculation..." << endl;

	// else haven't hit this one yet, so create an entry and dive along the path
	dr->paths = 0;
	dr->index = startIndex;
	dr->inProgress = true;
	dr->mtx.lock();
	//results.emplace(std::make_pair(startIndex, dr));
	results[startIndex] = dr;
	mapmtx.unlock();




	for (i = 0; i < MAX; i++)
	{
		size_t currIndex = startIndex + i;
		if (currIndex < adapterJolts.size())
		{
			if ((adapterJolts[currIndex] - startJolt) <= 3) 
			{
				if (currIndex >= (adapterJolts.size() - 1))
				{
					pathsHere++;
				}
				else // && currIndex < (adapterJolts.size()-1))
				{
					f[i] = std::async(FindPaths, adapterJolts, currIndex + 1, adapterJolts[currIndex], targetJolt);
					doF[i] = true;

					//pathsHere += FindPaths(adapterJolts, currIndex + 1, adapterJolts[currIndex], targetJolt);
				}
			}
		}
	}

	for (i = 0; i < MAX; i++)
	{
		if (doF[i])
		{
			//cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << " i=" << i << " paths before get results=" << pathsHere << endl;
			pathsHere += f[i].get();
			//cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << " i=" << i << " paths after get results=" << pathsHere << endl;
		}
	}

	// calculation done, so update the entry
	mapmtx.lock();
	currResults = results.find(startIndex);
	if (currResults != results.end())
	{
		currResults->second->paths = pathsHere;
		currResults->second->inProgress = false;
		// release everyone waiting for the results
		currResults->second->mtx.unlock();
	}
	else
	{
		cout << "Couldn't find the entry that I was working on! " << startIndex << endl;
	}
	mapmtx.unlock();

	//cout << " FindPaths() start index = " << startIndex << ", Jolts start=" << startJolt << ", target=" << targetJolt << ". Calculation complete: " << pathsHere << endl;
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
