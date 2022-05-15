#include <iostream>
#include "faculty.h";

Faculty::Faculty()
{
}
Faculty::Faculty(string institute, string name, int studentCount)
{
	this->institute = institute;
	this->name = name;
	this->studentCount = studentCount;
}
Faculty::Faculty(const Faculty& obj)
{
	this->institute = obj.institute;
	this->name = obj.name;
	this->studentCount = obj.studentCount;
}
Faculty::~Faculty()
{
}
string Faculty::getInstitute() const
{
	return institute;
}
int Faculty::getStudentCount() const
{
	return studentCount;
}