// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>    // std::sort
#include <map>
#include <mutex>

#include <thread>
#include <future>


#include "FileLoad.h"

using namespace std;


int PartA(vector<string>& lines);
int PartB(vector<string>& lines);


int main(int argc, char** argv)
{
	ShowInputs(argc, argv);

	if (argc != 2)
		return -2;

	vector<string> lines;
	if (!OpenAndReadInput(argv[1], lines))
	{
		return -1;
	}

	cout << "Day 11 part a : " << PartA(lines) << endl;
	cout << "Day 11 part b : " << PartB(lines) << endl;

	return 0;
}



int PartA(vector<string>& lines)
{
	return 0;

}


int PartB(vector<string>& lines)
{
	cout << "TBD" << endl;
	return 0;
}
