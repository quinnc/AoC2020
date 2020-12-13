// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "FileLoad.h"

using namespace std;

int PartA(vector<string>& lines);

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


	cout << " Sum of counts = " << PartA(lines) << endl;

	return 0;

}

#define NUMQ 26

void FindYeses(string line, bool yeses[NUMQ])
{
	int index=-1;
	for (size_t c = 0; c < line.length(); c++)
	{
		index = line[c] - 'a';
		//cout << "found " << line[c] << " setting index =" << index << endl;
		if (index >= 0 && index < NUMQ)
			yeses[index] = true;
		else
			cout << " index is invalid!!!! " << endl;
	}
}

int NumYeses(bool yeses[NUMQ])
{
	int yescnt = 0;
	for (size_t b = 0; b < NUMQ; b++)
		if (yeses[b])
			yescnt++;

	return yescnt;
}

void ResetYeses(bool yeses[NUMQ])
{
	for (size_t y = 0; y < NUMQ; y++)
	{
		yeses[y] = false;
	}
}

void MatchAny(bool yeses[NUMQ], bool match)
{
	for (size_t y = 0; y < NUMQ; y++)
	{
		if (yeses[y] == match)
			cout << " index=" << y << " matches " << match << endl;
	}

}

int PartA(vector<string>& lines)
{
	bool yeses[NUMQ] = { false };
	int totalCounts = 0;

	for (size_t line = 0; line < lines.size(); line++)
	{
		if (lines[line] == "")
		{
			totalCounts += NumYeses(yeses);
			ResetYeses(yeses);
			MatchAny(yeses, true);
			continue;
		}

		// else
		FindYeses(lines[line], yeses);
	}

	// in case there wasn't a blank line at the end of the file
	totalCounts += NumYeses(yeses);

	return totalCounts;
}