// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>


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


int ManhattanDistance(int x, int y)
{
	//cout << " distance? x=" << x << ", abs(x)=" << abs(x) << ", y=" << y << ", abs(y)=" << abs(y) << endl;
	return (abs(x) + abs(y));
}




int PartA(vector<string>& lines)
{
	char currDir = 'E';
	int currX = 0;
	int currY = 0;

	for (auto line : lines)
	{
		//cout << endl;
		//cout << " Current line >>" << line << "<<" << endl;
		// turn right 90 deg or left 270 deg
		if (((line[0] == 'R') && (line[1] == '9')) ||
			((line[0] == 'L') && (line[1] == '2')))
		{
			////cout << "turning from " << currDir;
			switch (currDir)
			{
			case 'N':
				currDir = 'E';
				break;

			case 'E':
				currDir = 'S';
				break;

			case 'S':
				currDir = 'W';
				break;

			case 'W':
				currDir = 'N';
				break;

			default:
				throw std::exception("unkonw dir");
			}

			//cout << " to " << currDir << endl;
			continue;
		}

		// turn right 270 or left 90 degrees
		if (((line[0] == 'R') && (line[1] == '2')) ||
			((line[0] == 'L') && (line[1] == '9')))
		{

			//cout << " turning from " << currDir;
			switch (currDir)
			{
			case 'N':
				currDir = 'W';
				break;

			case 'E':
				currDir = 'N';
				break;

			case 'S':
				currDir = 'E';
				break;

			case 'W':
				currDir = 'S';
				break;

			default:
				throw std::exception("unkonw dir");
			}

			//cout << " to " << currDir << endl;
			continue;
		}


		if (((line[0] == 'R') && (line[1] == '1')) ||
			((line[0] == 'L') && (line[1] == '1')))
		{
			//cout << "turning from " << currDir;
			switch (currDir)
			{
			case 'N':
				currDir = 'S';
				break;

			case 'E':
				currDir = 'W';
				break;

			case 'S':
				currDir = 'N';
				break;

			case 'W':
				currDir = 'E';
				break;

			default:
				throw std::exception("unkonw dir");
			}

			//cout << " to " << currDir << endl;
			continue;
		}

		int dist = stoi(line.substr(1));
		if (line[0] == 'F')
		{
			//cout << " changing Forward to " << currDir << endl;
			line[0] = currDir;
		}



		switch (line[0])
		{
		case 'N':
			currY -= dist;
			//cout << " going North " << dist << endl;
			break;

		case 'E':
			currX += dist;
			//cout << " going East " << dist << endl;
			break;

		case 'S':
			currY += dist;
			//cout << " going South " << dist << endl;
			break;

		case 'W':
			//cout << " going West " << dist << endl;
			currX -= dist;
			break;

		default:
			throw std::exception("unknown walk direction!");
		}

	}

	int d = ManhattanDistance(currX, currY);
	//cout << " net distance travelled: " << d << endl;

	return d;
}

int PartB(vector<string>& lines)
{
	int boatX = 0;
	int boatY = 0;
	int wayX = 10;
	int wayY = -1;

	for (auto line : lines)
	{
		cout << endl;
		cout << " Current line >>" << line << "<<" << endl;
		// turn right 90 deg or left 270 deg
		if (((line[0] == 'R') && (line[1] == '9')) ||
			((line[0] == 'L') && (line[1] == '2')))
		{
			cout << "turning from " << wayX << "," << wayY << endl;
			int xMult = -1;
			int yMult = 1;

			int tempY = wayY;
			wayY = wayX * yMult;
			wayX = tempY * xMult;

			cout << " to " << wayX << ", " << wayY << endl;
			continue;
		}

		// turn right 270 or left 90 degrees
		if (((line[0] == 'R') && (line[1] == '2')) ||
			((line[0] == 'L') && (line[1] == '9')))
		{
			cout << "turning from " << wayX << "," << wayY << endl;
			int xMult = 1;
			int yMult = -1;

			int tempY = wayY;
			wayY = wayX * yMult;
			wayX = tempY * xMult;

			cout << " to " << wayX << ", " << wayY << endl;
			continue;
		}


		if (((line[0] == 'R') && (line[1] == '1')) ||
			((line[0] == 'L') && (line[1] == '1')))
		{
			cout << "turning from " << wayX << "," << wayY;
			wayY = -1 * wayY;
			wayX = -1 * wayX;
			cout << " to " << wayX << "," << wayY << endl;
			continue;
		}

		int dist = stoi(line.substr(1));

		switch (line[0])
		{
		case 'F':
		{
			// move the boat in the direction of waypoint, multiplied by 'dist' times
			cout << endl;
			cout << " Action is FORWARD" << endl;
			cout << "Boat @ " << boatX << "," << boatY << endl;
			cout << "Way point @ " << wayX << "," << wayY << endl;
			int boatToWayX = wayX - boatX;
			int boatToWayY = wayY - boatY;

			cout << " Delta = " << boatToWayX << "," << boatToWayY << ", multiplier: " << dist << endl;
			boatX += (boatToWayX * dist);
			boatY += (boatToWayY * dist);
			cout << " after: Boat @ " << boatX << "," << boatY << endl;
			cout << endl;
		}
		break;

		case 'N':
			wayY -= dist;
			cout << " going North " << dist << endl;
			break;

		case 'E':
			wayX += dist;
			cout << " going East " << dist << endl;
			break;

		case 'S':
			wayY += dist;
			cout << " going South " << dist << endl;
			break;

		case 'W':
			cout << " going West " << dist << endl;
			wayX -= dist;
			break;

		default:
			throw std::exception("unknown walk direction!");
		}

	}

	int d = ManhattanDistance(boatX, boatY);
	cout << " net distance travelled: " << d << endl;

	return d;
}