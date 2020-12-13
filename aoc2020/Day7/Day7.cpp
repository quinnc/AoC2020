// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	//cout << "PART B::: Sum of counts = " << PartB(lines) << endl;

	return 0;

}


class Bag
{
public:
	map<string, int> contents;
	string name = "";
	bool containsShinyGold = false;

	Bag() { }

};

typedef map<string, Bag> Rules;

int ParseLine(const string & line, Rules& rules)
{
	int firstBags = line.find(" bags", 0);
	string name = line.substr(0, firstBags);

	//cout << " Bag name == " << name << endl;


	int containStart = line.find("contain ", firstBags);
	string recipeStr = line.substr(containStart + 8);

	//cout << "contents start == " << containStart << " recipe string ==" << recipeStr << "==" <<endl;
	Bag emptyBag;
	emptyBag.name = name;
	emptyBag.containsShinyGold = false;

	int noBagsStart = recipeStr.find("no other bags");
	//cout << " No other bags? " << noBagsStart << endl;
	if (noBagsStart == string::npos)
	{
		int nextBag = recipeStr.find("bag");
		//cout << "Next part ==" << recipeStr << "==, next bag @ " << nextBag << endl;
		while (nextBag != string::npos)
		{
			int nextDigit = recipeStr.find_first_of("0123456789");
			recipeStr = recipeStr.substr(nextDigit);
			// now that shortened the recipe, update the nextbag
			nextBag = recipeStr.find("bag");

			//cout << "after skipping ahead to the next digit >>" << recipeStr << "<<" << endl;
			// 1 digit
			int num = atoi(recipeStr.substr(0, 1).c_str());

			string partname = recipeStr.substr(2, nextBag - 3);

			//cout << "  Container " << name << " contains --" << num << "-- bags of colour --" << partname <<"--" << endl;

			emptyBag.contents[partname] = num;
			if (partname == "shiny gold")
				emptyBag.containsShinyGold = true;

			// move tot he next containee
			recipeStr = recipeStr.substr(nextBag + 3);
			nextBag = recipeStr.find("bag");
			//cout << "Next part = " << recipeStr << ", next bag @ " << nextBag << endl;
		}

	}

	rules[name] = emptyBag;

	return 0;
}


int ParseFile(vector<string>& lines, Rules& rules)
{

	for (size_t i = 0; i < lines.size(); i++)
		ParseLine(lines[i], rules);

	return 0;
}

bool CanContain(const  Bag& container, Rules& rules, const string& bagName)
{
	if (container.containsShinyGold)
		return true;
	for (auto& containee : container.contents)
	{
		if (CanContain(rules[containee.first], rules, bagName))
			return true;
	}

	return false;
}

int PartA(vector<string>& lines)
{
	Rules bagRules;

	ParseFile(lines, bagRules);

	int numContainShinyGold = 0;

	for (auto &rule : bagRules)
	{
		if (CanContain(rule.second, bagRules, "shiny gold"))
			numContainShinyGold++;
	}

	return numContainShinyGold;

}