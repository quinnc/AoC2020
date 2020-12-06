// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//#include <boost/algorithm>
#include <boost/algorithm/string.hpp> 

#include "FileLoad.h"


using namespace std;
using namespace boost::algorithm;

void Day4Part1(vector<string>& lines);
void Day4Part2(vector<string>& lines);

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

	//Day4Part1(lines);
	Day4Part2(lines);


	return 0;
}

#define SIZEOF(x) (sizeof(x)/sizeof(x[0]))
const char* keys[] = { "byr", "iyr", "eyr", "hgt","hcl", "ecl", "pid", "cid" };
enum class Key { BYR, IYR, EYR, HGT, HCL, ECL, PID, CID, MAX_KEY };

void Day4Part1(vector<string>& lines)
{

	bool foundKeys[SIZEOF(keys)] = { false, false, false, false, false, false, false };
	int validPassports = 0;
	int invalidPassports = 0;

	std::cout << __FUNCTION__ << "(): number of lines: " << lines.size() << endl;
	std::cout << __FUNCTION__ << "(): size of keys = " << SIZEOF(keys) << endl;

	for (size_t i = 0; i < lines.size(); i++)
	{
		//cout << i << ": >>" << lines[i] << "<<" << endl;

		std::string trimmed = boost::algorithm::trim_copy(lines[i]);
		if (trimmed.empty())
		{
			bool foundAllButCid = true;
			// check the state, then clear it
			for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
			{
				if (strncmp(keys[kIndex], "cid", 3) != 0)
				{
					foundAllButCid &= foundKeys[kIndex];
				}
				foundKeys[kIndex] = false;
			}


			// log success or failure
			if (foundAllButCid)
				validPassports++;
			else
				invalidPassports++;


			// start next
			continue;
		}

		std::vector<std::string> results;
		boost::split(results, trimmed, [](char c) {return c == ' ' || c == ':'; });

		for (size_t currPart = 0; currPart < results.size(); currPart += 2)
		{
			for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
			{
				if (results[currPart] == keys[kIndex])
				{
					//cout << "found part: " << keys[kIndex] << " mate:" << results[currPart + 1] << endl;

					foundKeys[kIndex] = true;
				}
			}
		}
	}


	// check for a valid passport when the file doesn't end in a blank line
	bool foundAllButCid = true;
	// check the state, then clear it
	for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
	{
		if (strncmp(keys[kIndex], "cid", 3) != 0)
		{
			foundAllButCid &= foundKeys[kIndex];
		}
		foundKeys[kIndex] = false;
	}


	// log success or failure
	if (foundAllButCid)
		validPassports++;
	else
		invalidPassports++;

	std::cout << "Passports valid=" << validPassports << ", invalid=" << invalidPassports << endl;
}



const char* eyeColourNames[] = { "amb","blu","brn","gry","grn","hzl","oth" };
enum class EyeColours { amb, blu, brn, gry, grn, hzl, oth, max };

void Day4Part2(vector<string>& lines)
{

	bool foundKeys[SIZEOF(keys)] = { false, false, false, false, false, false, false };
	int validPassports = 0;
	int invalidPassports = 0;

	std::cout << __FUNCTION__ << "(): number of lines: " << lines.size() << endl;
	std::cout << __FUNCTION__ << "(): size of keys = " << SIZEOF(keys) << endl;

	for (size_t i = 0; i < lines.size(); i++)
	{
		//std::cout << i << ": >>" << lines[i] << "<<" << endl;

		std::string trimmed = boost::algorithm::trim_copy(lines[i]);
		if (trimmed.empty())
		{
			bool foundAllButCid = true;
			// check the state, then clear it
			for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
			{
				if (strncmp(keys[kIndex], "cid", 3) != 0)
				{
					foundAllButCid &= foundKeys[kIndex];
				}
				foundKeys[kIndex] = false;
			}


			// log success or failure
			if (foundAllButCid)
				validPassports++;
			else
				invalidPassports++;


			// start next
			continue;
		}

		std::vector<std::string> results;
		boost::split(results, trimmed, [](char c) {return c == ' ' || c == ':'; });

		for (size_t currPart = 0; currPart < results.size(); currPart += 2)
		{
			if (results[currPart] == keys[(int)Key::BYR])
			{
				int birth = stoi(results[currPart + 1]);

				if (birth >= 1920 && birth <= 2002)
					foundKeys[(int)Key::BYR] = true;
				//else
					//cout << " INvalid birth year: " << birth << endl;
			}
			else if (results[currPart] == keys[(int)Key::CID])
			{
				foundKeys[(int)Key::CID] = true;
			}
			else if (results[currPart] == keys[(int)Key::ECL])
			{
				for (int colourIndex = (int)EyeColours::amb; colourIndex < (int)EyeColours::max; colourIndex++)
				{
					if (results[currPart + 1] == eyeColourNames[colourIndex])
					{
						foundKeys[(int)Key::ECL] = true;
						break;
					}
				}

				if (!foundKeys[(int)Key::ECL])
				{
					//cout << " Invalid eye colour: " << results[currPart + 1] << endl;
				}
			}
			else if (results[currPart] == keys[(int)Key::EYR])
			{
				int expires = stoi(results[currPart + 1]);

				if (expires >= 2020 && expires <= 2030)
					foundKeys[(int)Key::EYR] = true;
				//else
					//cout << " Invalid expiration year: >>" << expires << "<<" << endl;
			}
			else if (results[currPart] == keys[(int)Key::HCL])
			{
				size_t notIndex = 0;
				auto hairColour = results[currPart + 1];
				if (hairColour.length() == 7)
				{
					if (hairColour[0] == '#')
					{
						notIndex = hairColour.find_first_not_of("1234567890abcdefABCDEF", 1);
						if (notIndex == string::npos)
							foundKeys[(int)Key::HCL] = true;
					}
				}

				if (!foundKeys[(int)Key::HCL])
				{
					//cout << " Invalid hair colour: >>" << hairColour << "<<" << ", not index = " << notIndex << endl;
				}
			}
			else if (results[currPart] == keys[(int)Key::HGT])
			{
				string height = results[currPart + 1];
				if (height.length() >= 4)
				{
					string units = height.substr(height.length() - 2, 2);
					string sizeStr = height.substr(0, height.length() - 2);
					int size = stoi(sizeStr);


					if (units == "in")
					{
						if (size >= 59 && size <= 76)
							foundKeys[(int)Key::HGT] = true;
					}
					else if (units == "cm")
					{
						if (size >= 150 && size <= 193)
							foundKeys[(int)Key::HGT] = true;
					}
				}

				if (!foundKeys[(int)Key::HGT])
				{
					//cout << " Invalid height: >>" << height << "<<" << endl;
				}
			}
			else if (results[currPart] == keys[(int)Key::IYR])
			{
				int issued = stoi(results[currPart + 1]);

				if (issued >= 2010 && issued <= 2020)
					foundKeys[(int)Key::IYR] = true;
				//else
					//cout << " Invalid Issue year: >>" << issued << "<<" << endl;
			}
			else if (results[currPart] == keys[(int)Key::PID])
			{
				string pid = results[currPart + 1];
				if (pid.length() == 9)
				{
					size_t firstBad = pid.find_first_not_of("0123456789");
					if (firstBad == string::npos)
						foundKeys[(int)Key::PID] = true;
				}

				//if (!foundKeys[(int)Key::PID])
				//{
				//	cout << " Invalid passport ID: " << pid << endl;
				//}
			}
			else
			{
				(void)(currPart);
			}
		}
	}

	bool foundAllButCid = true;
	// check the state, then clear it
	for (auto kIndex = 0; kIndex < SIZEOF(keys); kIndex++)
	{
		if (strncmp(keys[kIndex], "cid", 3) != 0)
		{
			foundAllButCid &= foundKeys[kIndex];
		}
		foundKeys[kIndex] = false;
	}


	// log success or failure
	if (foundAllButCid)
		validPassports++;
	else
		invalidPassports++;

	std::cout << __FUNCTION__ << "(): Passports valid=" << validPassports << ", invalid=" << invalidPassports << endl;
}