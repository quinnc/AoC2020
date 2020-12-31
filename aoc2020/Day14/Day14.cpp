// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <vector>
#include <string>
#include <map>


//#include <boost/algorithm>
//#include <boost/algorithm/string.hpp> 


#include "FileLoad.h"

using namespace std;

typedef unsigned long long int ulli;

ulli PartA(vector<string>& lines);
ulli PartB(vector<string>& lines);


int main(int argc, char** argv)
{
	string name = argv[0];

	name = name.substr(name.find_last_of('\\')+1);

	ShowInputs(argc, argv);

	if (argc != 2)
	{
		cout << "Invalid number of args : " << argc << endl;
		return -2;
	}

	vector<string> lines;
	if (!OpenAndReadInput(argv[1], lines))
	{
		cout << "Opening and reading file failed." << endl;
		return -1;
	}

	cout << name << " part a : " << PartA(lines) << endl;
	cout << name << " part b : " << PartB(lines) << endl;

	return 0;
}

#define MASK_LEN 36ULL
#define KEEP_OP 1ULL
#define REPLACE_OP  0ULL

void GetMask(const string& line, ulli& mask, ulli& opMask)
{
	if (line.substr(0, 4) != "mask")
	{
		cout << "  LINE doesn't start with MASK! " << line << endl;
		return;
	}

	string maskStr = line.substr(7);

	size_t chIdx = 0;
	mask = 0;
	opMask = 0xFFFFFFFFFFFF;


	for (chIdx = 0; chIdx < maskStr.length(); chIdx++)
	{
		ulli currShift = MASK_LEN - chIdx;
		ulli op = (maskStr[chIdx] == 'X') ? (KEEP_OP) : (REPLACE_OP);

		// clear the bit and set it to the new op
		opMask = (opMask & ~(1ULL << currShift) ) | (op << currShift);
		
		ulli bit = 0;

		switch (maskStr[chIdx])
		{
		case 'X':
			bit = 1;
			break;

		case '1':
			bit = 1;
			break;

		case '0':
			bit = 0;
			break;

		default:
			cout << " ERROR !!!!! unknown bit value = " << maskStr[chIdx] << ", at index=" << chIdx << endl;
			break;
		}

		mask |= (bit << currShift);
	}

	cout << "final mask=" << mask << ", ops=" << opMask << endl;

}

void GetMemAndValue(const string& line, int& addr, ulli& value)
{
	addr = -1;
	value = 0;
	if (line.substr(0, 3) != "mem")
	{
		cout << "  LINE doesn't start with MEM! " << line << endl;
		return;
	}

	size_t rBracketPos = line.find(']');
	string addrStr = line.substr(4, rBracketPos - 4);
	cout << " ADDRESS: " << addrStr << endl;

	addr = stoi(addrStr);

	string valStr = line.substr(rBracketPos + 3);
	cout << " VALUE: " << valStr;

	value = stoull(valStr);

}

ulli DoMasking(const ulli& inValue, const ulli& bits, const ulli& opMask)
{
	ulli i = 0;
	ulli outVal = 0;

	for (i = 0; i < MASK_LEN; i++)
	{
		ulli currOp = (opMask >> i) & 0x1;
		if (currOp == KEEP_OP)
		{
			outVal |= (inValue & (1ULL << i));
		}
		else
		{
			outVal |= (bits & (1ULL << i));
		}

	}
	return outVal;
}


ulli PartA(vector<string>& lines)
{

	ulli bits, opMask;
	int addr = 0;;
	ulli value = 0;

	map<int, ulli> memory;


	GetMask(lines[0], bits, opMask);

	size_t curr = 1;
	while (curr < lines.size())
	{

		GetMemAndValue(lines[curr], addr, value);
		if (addr < 1)
		{
			cout << "ERROR invalid address! " << lines[curr] << endl;
			curr++;
			continue;
		}

		value = DoMasking(value, bits, opMask);

		memory.emplace(addr, value);
		curr++;
	}

	ulli sum = 0;

	for (auto m : memory)
	{
		sum += m.second;
	}

	return sum;
}

ulli PartB(vector<string>& lines)
{
	return -11;
}
