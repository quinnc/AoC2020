
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "FileLoad.h"

using namespace std;



bool OpenAndReadInput(char* filename, vector<string>& lines)
{
	fstream inputfile;
	string line;
	int lineCount = 0;
	inputfile.open(filename, ios::in);

	if (!inputfile.is_open())
	{
		cout << " Unable to open " << filename << endl;
		return false;
	}

	while (getline(inputfile, line))
	{
		//int cost = std::stoi(line);
		lines.push_back(line);
		lineCount++;
	}

	inputfile.close();
	return true;
}


void ShowInputs(int argc, char** argv)
{
	std::cout << "Hello World! argc=" << argc << std::endl;
	for (int i = 0; i < argc; i++)
		std::cout << i << " : " << argv[i] << std::endl;
}

