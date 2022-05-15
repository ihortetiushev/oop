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
	int buildingNo;
	Faculty faculty;
	vector<Room> rooms;

public:
	Dormitory();
	Dormitory(string street, int buildingNo, Faculty faculty, vector<Room> rooms);
	Dormitory(const Dormitory& obj);
	~Dormitory();
	//setterrs
	void setFaculty(Faculty faculty);
	void setStreet(string street);
	void setBuildingNo(int buildingNo);
	void setRooms(vector<Room> rooms);

	vector<Room> getRooms() const;
	int getBuildingNo() const;

	//public business logic methods
	string getFullAddressWithInstitutionName() const;
	bool addRoom(Room roomToAdd);
	double getAverageOccupancy() const;
	void enterRoom();
	vector<int> listRoomNumbers() const;
	Room* getByRoomNo(Room room);
	Room& getByRoomNo(int roomNo);
	Room* chooseRoom(string msg);
	void printAvailableRooms();
	void printInstituteStatistics();
	void outputRooms(ostream& out) const;

	//operators
	bool operator <(const Dormitory& arg2) const;
	bool operator +(const Room roomToAdd);//adding a room
};

istream& operator >>(istream& in, Dormitory& dormitory);
ostream& operator <<(ostream& out, const Dormitory& dormitory);
