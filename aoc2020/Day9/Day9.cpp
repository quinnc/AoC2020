// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>

#include "FileLoad.h"

using namespace std;

int PartA(vector<string>& lines, int preamble);
int PartB(vector<string>& lines);

int main(int argc, char** argv)
{
	std::cout << "Hello World!\n";

	ShowInputs(argc, argv);

	if (argc != 3)
		return -2;

	vector<string> lines;
	if (!OpenAndReadInput(argv[1], lines))
	{
		return -1;
	}

	int preambleDepth = atoi(argv[2]);

	if (preambleDepth > (int)lines.size())
		return -3;

	cout << " Part A: first number not a sum of previous " << preambleDepth << " is " << PartA(lines, preambleDepth) << endl;
	

	return 0;

}


bool FoundAdders(int total, list<int>& source)
{
	if (source.size() <= 1)
		return false;

	int first = source.front();
	source.pop_front();

	for (auto second = source.cbegin(); second != source.cend(); second++)
	{
		int tmp = first + *second;
		if (tmp == total)
		{
			// put back
			source.push_front(first);
			return true;
		}

	}

	bool next = FoundAdders(total, source);
	// put bakc
	source.push_front(first);
	return next;
}



int PartA(vector<string>& lines, int preamble)
{
	list<int> adders;

	for (size_t i = 0; i < (size_t)preamble; i++)
	{
		adders.push_back(stoi(lines[i]));
	}

	for (size_t curr = preamble; curr < lines.size(); curr++)
	{
		// now look for the first that doesn't add up
		int newSum = stoi(lines[curr]);
		bool added = FoundAdders(newSum, adders);

		if (!added)
			return newSum;

		// else found 2 numbers that added up to it, so try the next
		adders.pop_front();
		adders.push_back(newSum);
	}

	return -1;

}