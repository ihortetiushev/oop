#include "utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

stringstream readTextFileAsStringstream(string fileName)
{
	ifstream inFile(fileName);
	if (!inFile)
	{
		string errMsg = "File " + fileName + " not found";
		cerr << errMsg << endl;
		system("pause");
		throw errMsg;
	}

	stringstream content;
	content << inFile.rdbuf();
	inFile.close();
	return content;
}

void out(string text, ofstream& outFile, ostream& console) 
{
	console << text << endl;
	outFile << text << endl;
}

void process(stringstream& inputDate, set<string> EXCEPTIONS)
{
	vector<string> foundFromExceptionList;
	vector<string> wordsWithoutExceptions;
	vector<string> allWords;

	string word;
	while (inputDate >> word) 
	{
		allWords.push_back(word);
		if (EXCEPTIONS.find(word) != EXCEPTIONS.end())
		{//found exception
			foundFromExceptionList.push_back(word + " - зi списку");
		}
		else 
		{//ordinary word
			wordsWithoutExceptions.push_back(word);
		}
	}
	ofstream outFile("out.txt");
	for (auto exception : foundFromExceptionList) 
	{
		out(exception, outFile, cout);
	}

	map<char, vector<string>> wordsByFirdsLetter = wordsStartingFromLetter(allWords);

	for (auto currentWord : wordsWithoutExceptions)
	{
		char lastLetter = getLastWordLetter(currentWord);
		auto found = wordsByFirdsLetter.find(lastLetter);
		if (found != wordsByFirdsLetter.end())
		{//found word starting from last letter of pervious word
			string text = currentWord + " -> " + toString(found->second) + "(" + to_string(found->second.size()) + ")";
			out(text, outFile, cout);
		}
	}
	outFile.close();
}

map<char, vector<string>> wordsStartingFromLetter(vector<string> allWorlds)
{
	map<char, vector<string>> wordsByFirdsLetter;
	for (auto word : allWorlds)
	{
		char firstLetter = word[0];
		if (wordsByFirdsLetter.find(firstLetter) == wordsByFirdsLetter.end())
		{//no words starting from firstLetter yet
			vector<string> words;
			words.push_back(word);
			wordsByFirdsLetter.insert({ firstLetter, words });
		}
		else 
		{
			auto found = wordsByFirdsLetter.find(firstLetter);
			found->second.push_back(word);
		}
	}
	return wordsByFirdsLetter;
}

char getLastWordLetter(string word) 
{
	int lastIndex = word.length() - 1;
	char last;
	last = word[lastIndex];
	if (last == 'ь') 
	{
		int prevIndex = lastIndex - 1;
		last = word[prevIndex];
	}
	return last;
}

string toString(vector<string> toPrint)
{
	string out = "";
	for (auto item : toPrint) 
	{
		out = out + " " + item;
	}
	return out;
}