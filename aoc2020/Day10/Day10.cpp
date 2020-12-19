// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>    // std::sort

#include "FileLoad.h"

using namespace std;

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
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

int PartA()
{
	list<int> adapterJolts;

	for (size_t i = 0; i < (size_t)preamble; i++)
	{
		adders.push_back(stoi(lines[i]));
	}

	std::sort(adapterJolts.begin(), adapterJolts.end());
}