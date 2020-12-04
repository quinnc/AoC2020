// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int CheckPasswords(vector<string>& lines);
bool IsPasswordValid(string& passwordLine);
void ShowInputs(int argc, char** argv);
void ParseRule(string& rule, int& min, int& max, char& letter);
bool CheckPassword(string& ps, int min, int max, char letter);
bool CheckPasswordPart2(string& ps, int min, int max, char letter);

bool OpenAndReadInput(char* filename, vector<string>& lines);

int main(int argc, char** argv)
{
	std::cout << "Hello World!\n";

	ShowInputs(argc, argv);

	vector<string> passwordLines;

	if (argc != 2)
		return -2;

	if (!OpenAndReadInput(argv[1], passwordLines))
		return -1;

	int validPasswords = 0;

	validPasswords = CheckPasswords(passwordLines);
	return 0;
}

void ShowInputs(int argc, char** argv)
{
	std::cout << "Hello World! argc=" << argc << std::endl;

	for (int i = 0; i < argc; i++)
		std::cout << i << " : " << argv[i] << std::endl;
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

int CheckPasswords(vector<string>& lines)
{
	int valid = 0;
	int invalid = 0;

	for (auto line : lines)
	{
		bool isValid = IsPasswordValid(line);
		if (isValid)
			valid++;
		else
			invalid++;
	}

	cout << "Valid passwords: " << valid << endl;
	cout << "Invalid passwords: " << invalid << endl;
	cout << "Total passwords: " << valid + invalid << endl;

	return 0;
}

bool IsPasswordValid(string& passwordLine)
{
	string rule;
	string pw;

	size_t colonLoc = passwordLine.find(':');

	rule = passwordLine.substr(0, colonLoc);
	pw = passwordLine.substr(colonLoc + 2, string::npos);

	//cout << "rule = " << rule << ", password = " << pw << endl;
	int min, max;
	char letter;

	ParseRule(rule, min, max, letter);
	return CheckPasswordPart2(pw, min, max, letter);
	
}


void ParseRule(string& rule, int& min, int& max, char& letter)
{
	string minStr;
	string maxStr;
	string secondHalf;
	string charStr;
	size_t dashLoc = rule.find('-');
	size_t spaceLoc = rule.find(' ');

	minStr = rule.substr(0, dashLoc);
	maxStr = rule.substr(dashLoc + 1, spaceLoc - dashLoc);
	charStr = rule.substr(spaceLoc + 1, string::npos);

	min = stoi(minStr);
	max = stoi(maxStr);
	if (min > max)
	{
		int t = min;
		min = max;
		max = t;
	}
	letter = charStr[0];

	//cout << "Min= " << min << ", Max= " << max << ", Letter= " << letter << endl;
}

bool CheckPassword(string& ps, int min, int max, char letter)
{
	int foundCount = 0;

	for (int i = 0; i < ps.length(); i++)
	{
		if (letter == ps[i])
			foundCount++;
	}

	return ((foundCount >= min) && (foundCount <= max));
}

bool CheckPasswordPart2(string& ps, int min, int max, char letter)
{
	//cout << ps << ", l=" << ps.length() << ", max=" << max << endl;
	if (ps.length() < max)
		return false;

	//cout << "expected = " << letter << ", @min = " << ps[min - 1] << ", @max = " << ps[max - 1] << endl;
	return ((ps[min - 1] == letter) == (ps[max - 1] != letter));
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
