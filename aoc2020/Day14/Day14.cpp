// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <vector>
#include <string>


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


ulli PartA(vector<string>& lines)
{
	return -10;
}

ulli PartB(vector<string>& lines)
{
	return -11;
}
