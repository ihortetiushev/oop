#include <iostream>
#include "utils.h"
#include <set>
#include <sstream>


using namespace std;
const set<string> EXCEPTIONS = { "день", "осенью", "лесов", "короче", "Пушкин"};

int main()
{
    setlocale(LC_ALL, "Russian");
    stringstream content = readTextFileAsStringstream("inputData.txt");
	process(content, EXCEPTIONS);
}
