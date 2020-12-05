// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void ShowInputs(int argc, char** argv);
bool OpenAndReadInput(char* filename, vector<string>& lines);
void SlideHill(vector<string>& l, int initX, int initY, int slopeX, int slopeY, int& treesHit, int& openSquares);

int main(int argc, char** argv)
{
	vector<string> lines;

	std::cout << "Hello World!\n";

	ShowInputs(argc, argv);

	if (argc < 2)
		return -2;

	if (!OpenAndReadInput(argv[1], lines))
	{
		return -1;
	}

	int treesHit = 0;
	int openSquares = 0;

	SlideHill(lines, 0, 0, 3, 1, treesHit, openSquares);

	cout << "Tree hit = " << treesHit << endl;
	cout << "Open squares = " << openSquares << endl;
	cout << "Total steps = " << treesHit + openSquares << endl;
	cout << "Total lines = " << lines.size() << endl;

	return 0;
}

void ShowInputs(int argc, char** argv)
{
	
	//std::cout << "Hello World! argc=" << argc << std::endl;

	for (int i = 0; i < argc; i++)
		std::cout << i << " : " << argv[i] << std::endl;
}


bool OpenAndReadInput(char* filename, vector<string>& lines)
{
	fstream inputfile;
	string line;

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
	}

	inputfile.close();
	return true;
}

void SlideHill(vector<string>& l, int initX, int initY, int slopeX, int slopeY, int& treesHit, int& openSquares)
{
	if (initY >= l.size())
		return;

	if (initX >= l[initY].length())
		initX -= l[initY].length();

	if (initX < 0)
		initX += l[initY].length();

	//[0] = ".........#.#.#.........#.#....."
	//cout << "x=" << initX << ", y=" << initY << ", current square = " << l.at(initY).at(initX) << endl;

	if (l.at(initY).at(initX) == '#')
		treesHit++;
	else
		openSquares++;

	initX += slopeX;
	initY += slopeY;

	SlideHill(l, initX, initY, slopeX, slopeY, treesHit, openSquares);
}
