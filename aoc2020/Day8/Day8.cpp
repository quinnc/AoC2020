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
	cout << "PART B::: fixed code accumulator = " << PartB(lines) << endl;

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


OpCodes GetOpCode(string& line)
{
	string opstr = line.substr(0, 3);

	if (opstr == OpCodeStrs[0])
		return OpCodes::acc;

	if (opstr == OpCodeStrs[1])
		return OpCodes::nop;

	if (opstr == OpCodeStrs[2])
		return OpCodes::jmp;

	throw std::exception("unknown op code!");
}

void RunCode(vector<string>& code, bool& cleanFinish, bool& infinite, bool& inLalaland, int& accum)
{
	accum = 0;
	size_t currLine = 0;
	unordered_map<int, int> visitedLines;
	string instr;

	cleanFinish = false;
	infinite = false;
	inLalaland = false;


	while (currLine >= 0 && currLine < code.size() && visitedLines.find(currLine) == visitedLines.end())
	{
		visitedLines.insert(make_pair(currLine, currLine));
		instr = code[currLine].substr(0, 3);

		//cout << "Current line: " << lines[currLine] << ", instruction= >>" << instr << "<<" << ", accumulator=" << accum << ", line num=" << currLine << endl;

		OpCodes op = GetOpCode(code[currLine]);

		switch (op)
		{
		case OpCodes::nop:
			currLine++;
			break;

		case OpCodes::acc:
		{
			int val = stoi(code[currLine].substr(4));
			accum += val;
			currLine++;
			break;
		}
		case OpCodes::jmp:
		{
			int val = stoi(code[currLine].substr(4));
			currLine += val;
			break;
		}
		}
	}


	inLalaland = (currLine < 0 || currLine > code.size());

	cleanFinish = (currLine == code.size());

	infinite = (currLine >= 0 && currLine < code.size());

}


int PartA(vector<string>& lines)
{
	int accum = 0;
	size_t currLine = 0;
	unordered_map<int, int> visitedLines;
	string instr;

	while (currLine < lines.size() && visitedLines.find(currLine) == visitedLines.end())
	{
		visitedLines.insert(make_pair(currLine, currLine));
		instr = lines[currLine].substr(0, 3);

		//cout << "Current line: " << lines[currLine] << ", instruction= >>" << instr << "<<" << ", accumulator=" << accum << ", line num=" << currLine << endl;

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


int PartB(vector<string>& lines)
{
	int totalLines = lines.size();
	int curr;
	string savedLine;
	string newLine;

	int accum;

	for (curr = 0; curr < totalLines; curr++)
	{
		savedLine = lines[curr];


		OpCodes op = GetOpCode(savedLine);

		switch (op)
		{
		case OpCodes::jmp:
			newLine = OpCodeStrs[(int)OpCodes::nop] + savedLine.substr(3);
			break;

		case OpCodes::nop:
			newLine = OpCodeStrs[(int)OpCodes::jmp] + savedLine.substr(3);
			break;

		default:
			// try another
			continue;
		}

		lines[curr] = newLine;

		bool clean, inf, lala;
		RunCode(lines, clean, inf, lala, accum);

		lines[curr] = savedLine;

		if (clean)
			return accum;
	}

	return -1;
}
