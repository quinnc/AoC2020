// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//#include <boost/algorithm>
#include <boost/algorithm/string.hpp> 

#include "FileLoad.h"


using namespace std;
using namespace boost::algorithm;

void Day4Part1(vector<string>& lines);

int main(int argc, char** argv)
{
	std::cout << "Hello World!\n";

	ShowInputs(argc, argv);

	if (argc < 2)
		return -2;

	vector<string> lines;
	if (!OpenAndReadInput(argv[1], lines))
	{
		return -1;
	}

	Day4Part1(lines);


	return 0;
}

#define SIZEOF(x) (sizeof(x)/sizeof(x[0]))
const char* keys[] = { "byr", "iyr", "eyr", "hgt","hcl", "ecl", "pid", "cid" };

void Day4Part1(vector<string>& lines)
{

	bool foundKeys[SIZEOF(keys)] = { false, false, false, false, false, false, false };
	int validPassports = 0;
	int invalidPassports = 0;

	cout << "number of lines: " << lines.size() << endl;
	cout << "size of keys = " << SIZEOF(keys) << endl;

	for (int i = 0; i < lines.size(); i++)
	{
		cout << i << ": >>" << lines[i] << "<<" << endl;
		
		
		std::string trimmed = boost::algorithm::trim_copy(lines[i]);
		if (trimmed.empty())
		{
			bool foundAllButCid = true;
			// check the state, then clear it
			for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
			{
				if (strncmp(keys[kIndex], "cid", 3) != 0)
				{
					foundAllButCid &= foundKeys[kIndex];
				}
				foundKeys[kIndex] = false;
			}


			// log success or failure
			if (foundAllButCid)
				validPassports++;
			else
				invalidPassports++;


			// start next
			continue;
		}

		std::vector<std::string> results;
		boost::split(results, trimmed, [](char c) {return c == ' ' || c == ':'; });

		for (auto currPart = 0; currPart < results.size(); currPart += 2)
		{
			for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
			{
				if (results[currPart] == keys[kIndex])
				{
					cout << "found part: " << keys[kIndex] << " mate:" << results[currPart + 1] << endl;
					foundKeys[kIndex] = true;
				}
			}
		}
	}

	//if (false)
	{
		bool foundAllButCid = true;
		// check the state, then clear it
		for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
		{
			if (strncmp(keys[kIndex], "cid", 3) != 0)
			{
				foundAllButCid &= foundKeys[kIndex];
			}
			foundKeys[kIndex] = false;
		}


		// log success or failure
		if (foundAllButCid)
			validPassports++;
		else
			invalidPassports++;
	}

	cout << "Passports valid=" << validPassports << ", invalid=" << invalidPassports << endl;
}