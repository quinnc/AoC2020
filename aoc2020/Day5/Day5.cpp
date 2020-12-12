// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "FileLoad.h"

using namespace std;

int HighestId(vector<string>& lines);
int MissingId(vector<string>& lines);


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

	//cout << "Highest seat id = " << HighestId(lines) << endl;
	MissingId(lines);
}

int GetRow(string rowpartitions)
{
	//cout << " Interpretting row: " << rowpartitions << endl;
	int currMin = 0;
	int currMax = 127;
	int middle = currMax / 2;

	for (size_t i = 0; i < rowpartitions.length(); i++)
	{
		if (rowpartitions[i] == 'F')
			currMax = middle;
		else
			currMin = middle + 1;

		middle = (currMin + currMax) / 2;
		//cout << "i=" << i << "; char=" << rowpartitions[i] << "; Min=" << currMin << "; Max=" << currMax << "; middle=" << middle << endl;

	}

	//cout << " Min=" << currMin << "; Max=" << currMax << "; middle=" << middle << endl;

	return middle;
}


int GetColumn(string colPartitions)
{
	//cout << " Interpretting columns: " << colPartitions << endl;

	int currMin = 0;
	int currMax = 7;
	int middle = currMax / 2;

	for (size_t i = 0; i < colPartitions.length(); i++)
	{
		if (colPartitions[i] == 'L')
			currMax = middle;
		else
			currMin = middle + 1;

		middle = (currMin + currMax) / 2;
		//cout << "i=" << i << "; char=" << colPartitions[i] << "; Min=" << currMin << "; Max=" << currMax << "; middle=" << middle << endl;

	}

	//cout << " Min=" << currMin << "; Max=" << currMax << "; middle=" << middle << endl;
	return middle;
}

int SeatId(int col, int row)
{

	return col * 8 + row;
}

int HighestId(vector<string>& lines)
{
	int currentHigh = 0;

	for (size_t i = 0; i < lines.size(); i++)
	{
		//cout << "Current line == " << lines[i] << endl;
		int row = GetRow(lines[i].substr(0, 7));
		int col = GetColumn(lines[i].substr(7, 3));
		int id = SeatId(row, col);

		//cout << "  Row =" << row << ", col=" << col << ", id =" << id << endl;
		if (id > currentHigh)
			currentHigh = id;
	}
	return currentHigh;
}


// part b
int MissingId(vector<string>& lines)
{
#define totRow 128
#define totCol 8
	bool occupied[totRow][totCol];
	int id = 0;

	for (size_t i = 0; i < lines.size(); i++)
	{
		//cout << "Current line == " << lines[i] << endl;
		int row = GetRow(lines[i].substr(0, 7));
		int col = GetColumn(lines[i].substr(7, 3));
		
		occupied[row][col] = true;
	}

	// find empty
	for (int row2 = 0; row2 < totRow; row2++)
		for (int col2 = 1; col2 < totCol; col2++)
		{
			if (!occupied[row2][col2])
				if (occupied[row2][col2 - 1] && occupied[row2][col2 + 1])
				{
					id = SeatId(row2, col2);
					cout << "Found empty seat at row=" << row2 << ", col=" << col2 << ", id=" << id << endl;
				}
		}

	return id;
}

