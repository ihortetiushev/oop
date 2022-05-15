#include <string>
#include <iostream>
#include "utils.h"
using namespace std;

bool isNumeric(string str) 
{
	for (unsigned i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false; //when one non numeric value is found, return false
	return true;
}
int getNumberFromConsole(string consoleMsg, int minValue, int maxValue)
{
	string tmpStr;
	bool wrongInput;
	do
	{
		cout << consoleMsg;
		getline(cin >> ws, tmpStr);
		wrongInput = !isNumeric(tmpStr) ||
			isNumeric(tmpStr) && stoi(tmpStr) < minValue
			||
			isNumeric(tmpStr) && stoi(tmpStr) > maxValue;
		if (wrongInput)
		{
			cout << "Wrong input. Try again." << endl;
		}
	} while (wrongInput);
	return stoi(tmpStr);
}
string getStrFromConsole(string consoleMsg)
{
	string str;
	cout << consoleMsg;
	getline(cin >> ws, str);
	return str;
}
void clearScreen()
{
	cout << "\x1B[2J\x1B[H";
}