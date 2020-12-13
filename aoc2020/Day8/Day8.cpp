// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

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


	cout << "PART A::: number of suitcase that can contain shiny gold = " << PartA(lines) << endl;
	cout << "PART B::: bags in shiny gold = " << PartB(lines) << endl;

	return 0;

}

