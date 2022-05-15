#pragma once

#include <iostream>
#include <vector>
#include "faculty.h"
#include "room.h"

using namespace std;

class Dormitory
{
private:
	string street;
	string buildingNo;
	Faculty faculty;
	vector<Room> rooms;

public:
	Dormitory();
	Dormitory(string street, string buildingNo, Faculty faculty, vector<Room> rooms);
	Dormitory(const Dormitory& obj);
	~Dormitory();
	//setterrs
	void setFaculty(Faculty faculty);
	void setStreet(string street);
	void setBuildingNo(string buildingNo);
	void setRooms(vector<Room> rooms);

	vector<Room>& getRooms();

	//public business logic methods
	string getFullAddressWithInstitutionName() const;
	bool addRoom(Room roomToAdd);
	double getAverageOccupancy() const;
	void enterRoom();
	vector<int> listRoomNumbers() const;
	Room* getByRoomNo(Room room);
	Room& getByRoomNo(int roomNo);
	Room* chooseRoom(string msg);
	void addStudents();
	void removeStudents();
	void printAvailableRooms();
	void printInstituteStatistics();

	//operators
	operator double() const;//used to get average occupancy
	Dormitory& operator =(const Dormitory& obj);
	bool operator +(const Room roomToAdd);//adding a room
};

istream& operator >>(istream& in, Dormitory& dormitory);
ostream& operator <<(ostream& out, Dormitory& dormitory);
