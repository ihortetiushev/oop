#pragma once
#include <string>
#include <set>
#include <vector>
#include <map>
using namespace std;

stringstream readTextFileAsStringstream(string fileName);
void process(stringstream& inputDate, set<string> EXCEPTIONS);
char getLastWordLetter(string word);
map<char, vector<string>> wordsStartingFromLetter(vector<string> allWorlds);
string toString(vector<string> toPrint);