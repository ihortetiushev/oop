#pragma once

#include <iostream> 

using namespace std;

class Faculty
{
private:
	string institute;
	string name;
	int studentCount = 0;
public:
	Faculty();
	Faculty(string institute, string name, int studentCount);
	Faculty(const Faculty& obj);
	~Faculty();
	string getInstitute() const;
	int getStudentCount() const;
};
