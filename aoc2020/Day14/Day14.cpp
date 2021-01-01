// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

//#include <boost/algorithm>
//#include <boost/algorithm/string.hpp> 


#include "FileLoad.h"

using namespace std;



ulli PartA(vector<string>& lines);
ulli PartB(vector<string>& lines);


int main(int argc, char** argv)
{
	string name = argv[0];

	name = name.substr(name.find_last_of('\\')+1);
	cout << " int max = " << std::hex << std::numeric_limits<int>::max() << endl;
	cout << " ulli max = " << std::hex << std::numeric_limits<ulli>::max() << endl;
	cout << std::dec;

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

	cout << "---> ABout to call Part A <----" << endl;
	ulli partAout = PartA(lines);
	cout << "---> Returned from Part A <----" << endl;

	cout << name << " part a : " << partAout << endl;

	cout << endl;
	cout << "---> About to call Part B <----" << endl;
	ulli partBout = PartB(lines);
	cout << "---> Returned from Part B <----" << endl;
	cout << name << " part b : 0x" << partBout << std::dec << " == "  << partBout << endl;

	return 0;
}

#define MASK_LEN 35ULL
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

	cout << " Got Mask --> mask=" << std::hex << mask << ", ops=" << std::hex << opMask << std::dec << endl;

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
	cout << " VALUE: " << valStr << endl;

	value = stoull(valStr);

}

ulli DoMasking(const ulli& inValue, const ulli& bits, const ulli& opMask)
{
	ulli i = 0;
	ulli outVal = 0;

	for (i = 0; i <= MASK_LEN; i++)
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

template <class IntType>
ulli SumMemory(const map<IntType, ulli>& memory)
{
	ulli sum = 0;

	for (auto& m : memory)
	{

		sum += m.second;
		//cout << " Adding memory: @" << m.first << " is " << m.second << ", total=" << sum << endl;
	}

	return sum;
}

ulli PartA(vector<string>& lines)
{

	ulli bits, opMask;
	int addr = 0;;
	ulli value = 0;

	map<int, ulli> memory;


	size_t curr = 0;
	while (curr < lines.size())
	{
		if (lines[curr][1] == 'a')
		{
			GetMask(lines[curr], bits, opMask);
		}
		else
		{
			GetMemAndValue(lines[curr], addr, value);
			if (addr < 1)
			{
				cout << "ERROR invalid address! " << lines[curr] << endl;
				curr++;
				continue;
			}

			value = DoMasking(value, bits, opMask);

			//memory.emplace(addr, value);
			memory[addr] = value;
			//cout << " Set address = " << addr << " to value=" << value << endl;
		}
		curr++;
	}

	
	return SumMemory(memory);
}


void MakeAddressList(const ulli& inAddr, const vector<int>& floatingBits, vector<ulli>& outAddrs)
{
	if (floatingBits.empty())
	{
		cout << " New address to set: " << std::hex<< inAddr << endl;
		outAddrs.push_back(inAddr);
		return;
	}

	vector<int> tempBits(floatingBits.size());
	std::copy(floatingBits.begin(), floatingBits.end(), tempBits.begin());

	int currBit = tempBits.back();
	tempBits.pop_back();

	ulli mask;

	// set the current bit to 1 and do the rest of the bits
	mask = inAddr | 1ULL << currBit;
	MakeAddressList(mask, tempBits, outAddrs);

	// clear the current bit and do the rest of the bits
	mask = inAddr & ~(1ULL << currBit);
	MakeAddressList(mask, tempBits, outAddrs);
}




void DoAddressMasking(const ulli& inAddress, const ulli& bits, const ulli& opMask, vector<ulli>& outAddrs)
{
	int i = 0;
	ulli outVal = 0;
	vector<int> floatingBits;

	for (i = 0; i <= MASK_LEN; i++)
	{
		ulli currOp = (opMask >> i) & 0x1;
		if (currOp == KEEP_OP)
		{
			floatingBits.push_back(i);
		}
		else
		{
			ulli currChangeBit = (bits >> i) & 0x1;
			if (currChangeBit == 1)
			{
				// set to 1
				outVal |= (1ULL << i);
			}
			else
			{
				//leave it unchanged
				outVal |= (inAddress & (1ULL << i));
			}
		}

	}

	cout << " Masked address: " << std::hex << outVal << ", incoming bit mask=" << bits << ", operation mask=" << opMask << endl;

	MakeAddressList(outVal, floatingBits, outAddrs);
}

ulli PartB(vector<string>& lines)
{
	ulli bits, opMask;
	int addr = 0;;
	ulli value = 0;

	map<ulli, ulli> memory;
	vector<ulli> addresses;


	size_t curr = 0;
	while (curr < lines.size())
	{
		addresses.clear();
		if (lines[curr][1] == 'a')
		{
			GetMask(lines[curr], bits, opMask);
		}
		else
		{
			GetMemAndValue(lines[curr], addr, value);
			if (addr < 1)
			{
				cout << "ERROR invalid address! " << lines[curr] << endl;
				curr++;
				continue;
			}

			DoAddressMasking(addr, bits, opMask, addresses);

			for (const auto& addr2 : addresses)
			{
				memory[addr2] = value;
				cout << " Set address = " << addr2 << " to value=" << value << endl;
			}
		}
		curr++;
	}


	return SumMemory(memory);

}
