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


bool SeatTransform(const vector<string>& before, vector<string>& after)
{
	size_t xMax = before[0].length();
	bool seatChanged = false;

	for (size_t y = 0; y < before.size(); y++)
	{
		for (size_t x = 0; x < xMax; x++)
		{
			if (x == 0)
				after.push_back(string());

			if (before[y].at(x) == '.')
			{
				after[y].push_back('.');
			}
			else if (before[y].at(x) == 'L')
			{
				bool foundOccupied = false;
				for (int yLook = -1; yLook <= 1; yLook++)
				{
					int currY = y + yLook;
					if (currY < 0)
						continue;

					if (currY >= (int)before.size())
						continue;

					for (int xLook = -1; xLook <= 1; xLook++)
					{
						int currX = x + xLook;

						if (currX < 0)
							continue;

						if (currX >= (int)xMax)
							continue;

						if (currX == 0 && currY == 0) // self
							continue;


						// if get here, then a valid location;
						if (before[currY].at(currX) == '#') // occupied
							foundOccupied = true;

					}
				}

				if (!foundOccupied)
				{
					after[y].push_back('#');
					seatChanged = true;;
				}
				else
				{
					after[y].push_back('L');
				}

			}
			else if (before[y].at(x) == '#')
			{
				int occupiedCount = 0;

				for (int yLook = -1; yLook <= 1; yLook++)
				{
					int currY = y + yLook;
					if (currY < 0)
						continue;

					if (currY >= (int)before.size())
						continue;

					for (int xLook = -1; xLook <= 1; xLook++)
					{
						int currX = x + xLook;

						if (currX < 0)
							continue;

						if (currX >= (int)xMax)
							continue;

						if (currX == 0 && currY == 0) // self
							continue;


						// if get here, then a valid location;
						if (before[currY].at(currX) == '#') // occupied
							occupiedCount++;

					}
				}

				if (occupiedCount >= 4)
				{
					after[y].push_back('L');
					seatChanged = true;;
				}
				else
				{
					after[y].push_back('#');
				}
			}
		}
	}

	return seatChanged;
}


void PrintSeatMap(const vector<string>& seats)
{
	for (auto row : seats)
		cout << row << endl;
}

unsigned int CountOccupied(const vector<string>& init)
{
	size_t xMax = init[0].length();
	unsigned int count = 0;

	for (size_t y = 0; y < init.size(); y++)
	{
		for (size_t x = 0; x < xMax; x++)
		{
			if (init[y].at(x) == '#')
				count++;
		}
	}

	return count;
}

template <class T>
void VectorCopy(const vector<T>& Src, vector<T>& Dest)
{
	Dest.clear();
	for (auto a : Src)
		Dest.push_back(a);
}

int PartA(vector<string>& lines)
{
	vector<string> init;
	vector<string> next;

	if (lines.size() < 3)
	{
		cout << " NOT ENOUGH LINES! " << endl;
		return -1;
	}

	int rounds = 0;
	bool transformDidChange = true;

	VectorCopy(lines, init);

	while (rounds < 100 && transformDidChange)
	{
		rounds++;
		cout << endl << endl;
		cout << "*************************" << endl;
		cout << "Round : " << rounds << endl;

		transformDidChange = SeatTransform(init, next);

		cout << "Before:" << endl;
		PrintSeatMap(init); 
		cout << endl << "After: " << endl;
		PrintSeatMap(next);

		VectorCopy(next, init);
		next.clear();
	}

	cout << "Rounds = " << rounds << endl;

	cout << " Number occupied = " << CountOccupied(init) << endl;
	

	return 0;

}


int PartB(vector<string>& lines)
{
	cout << "TBD" << endl;
	return 0;
}
