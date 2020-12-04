// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	int i;

    std::cout << "Hello World! argc=" << argc << std::endl;

	for (i = 0; i < argc; i++)
		std::cout << i << " : " << argv[i] << std::endl;

	fstream inputfile;
	string line;
	vector<int> costNums;

	inputfile.open(argv[1], ios::in);

	if (!inputfile.is_open())
	{
		cout << " Unable to open " << argv[1] << endl;
		return -1;
	}

	while (getline(inputfile, line))
	{
		int cost = std::stoi(line);
		costNums.push_back(cost);
	}

	int highest = 0;
	int highestOne = 0;
	int highestTwo = 0;

	for (auto first = costNums.begin(); first != costNums.end() - 1; first++)
	{
		int firstval = (*first);
		for (auto second = first + 1; second != costNums.end(); second++)
		{
			int secondval = (*second);
			auto sum = firstval + secondval;
			if (sum == 2020)
			{
				auto multresult = firstval * secondval;
				if (multresult > highest)
				{
					highest = multresult;
					highestOne = firstval;
					highestTwo = secondval;
				}
			}
		}
	}

	cout << " First number=" << highestOne << endl;
	cout << " Second number = " << highestTwo << endl;
	cout << " Highest multiplication result = " << highest << endl;
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
