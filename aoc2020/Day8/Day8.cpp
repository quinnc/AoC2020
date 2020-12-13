// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

#include "FileLoad.h"

using namespace std;

int PartA(vector<string>& lines);
int PartB(vector<string>& lines);

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


	cout << "PART A:::  accumlator = " << PartA(lines) << endl;
	//cout << "PART B::: bags in shiny gold = " << PartB(lines) << endl;

	return 0;

}

enum class OpCodes
{
	acc,
	nop,
	jmp
};

const char* const OpCodeStrs[] = {
	"acc",
	"nop",
	"jmp",
};


int PartA(vector<string>& lines)
{
	int accum = 0;
	int currLine = 0;
	unordered_map<int, int> visitedLines;
	string instr;

	while (visitedLines.find(currLine) == visitedLines.end())
	{
		visitedLines.insert(make_pair(currLine, currLine));
		instr = lines[currLine].substr(0, 3);

		cout << "Current line: " << lines[currLine] << ", instruction= >>" << instr << "<<" << ", accumulator=" << accum << ", line num=" << currLine << endl;

		if (instr == OpCodeStrs[(int)OpCodes::nop])
		{
			currLine++;
		}
		else if (instr == OpCodeStrs[(int)OpCodes::acc])
		{
			int val = stoi(lines[currLine].substr(4));
			accum += val;
			currLine++;
		}
		else if (instr == OpCodeStrs[(int)OpCodes::jmp])
		{
			int val = stoi(lines[currLine].substr(4));
			currLine += val;
		}
	}

	return accum;
}