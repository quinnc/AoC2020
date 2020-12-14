// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>    // std::sort

#include "FileLoad.h"

using namespace std;

unsigned long int PartA(const vector<string>& lines, int preamble);
unsigned long int PartB(const vector<string>& lines, unsigned long int sum);

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

	unsigned long int result = PartA(lines, preambleDepth);
	cout << " Part A: first number not a sum of previous " << preambleDepth << " is " << result << endl;

	cout << " Part B: add of the smallest and largest sums: " << PartB(lines, result) << endl;
	

	return 0;

}


bool FoundAdders(int total, list<unsigned long int>& source)
{
	if (source.size() <= 1)
		return false;

	unsigned long int first = source.front();
	source.pop_front();

	for (auto second = source.cbegin(); second != source.cend(); second++)
	{
		unsigned long int tmp = first + *second;
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



unsigned long int PartA(const vector<string>& lines, int preamble)
{
	list<unsigned long int> adders;

	for (size_t i = 0; i < (size_t)preamble; i++)
	{
		adders.push_back(stoi(lines[i]));
	}

	for (size_t curr = preamble; curr < lines.size(); curr++)
	{
		// now look for the first that doesn't add up
		unsigned long int newSum = strtoul(lines[curr].c_str(), nullptr, 10);
		bool added = FoundAdders(newSum, adders);

		if (!added)
			return newSum;

		// else found 2 numbers that added up to it, so try the next
		adders.pop_front();
		adders.push_back(newSum);
	}

	return 0;

}


/// <summary>
///  Find at least 2 contiguous numbers that add up to the sum.
/// </summary>
/// <param name="lines"></param>
/// <param name="sum"></param>
/// <returns></returns>
unsigned long int PartB(const vector<string>& lines, unsigned long int sum)
{
	vector<unsigned long int> codes;
	
	// make the lines into numbers;
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i] == "")
			continue;


		codes.push_back(strtoul(lines[i].c_str(), nullptr, 10));
	}

	bool foundMatch = false;
	vector<unsigned long int> addParts;

	for (size_t i = 0; i < codes.size()-1; i++)
	{
		unsigned long int total = codes[i];
		
		addParts.clear();
		addParts.push_back(codes[i]);
		

		for (size_t j = i + 1; j < codes.size(); j++)
		{
			total += codes[j];
			addParts.push_back(codes[j]);

			if (total == sum)
			{
				foundMatch = true;
				break;
			}
		}
		
		if (foundMatch)
			break;
	}


	cout << "found match? " << (foundMatch?"true":"false") << endl;
	cout << "size of parts? " << addParts.size() << endl;
	for (auto p : addParts)
	{
		cout << " " << p;
	}
	cout << endl;
	// get the lowest and highest in addParts
	
	std::sort(addParts.begin(), addParts.end());
	unsigned int answer = *(addParts.begin()) + *(addParts.end() - 1);
	return answer;
}

