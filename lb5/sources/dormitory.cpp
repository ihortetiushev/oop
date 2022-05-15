#include <iostream>
#include <vector>
#include <string>
#include "dormitory.h"
#include "room.h"
#include "utils.h"


using namespace std;

Dormitory::Dormitory()
{
}
Dormitory::Dormitory(string street, string buildingNo, Faculty faculty, vector<Room> rooms)
{
	this->street = street;
	this->buildingNo = buildingNo;
	this->faculty = faculty;
	this->rooms = rooms;
}
Dormitory::Dormitory(const Dormitory& obj)
{
	this->street = obj.street;
	this->buildingNo = obj.buildingNo;
	this->faculty = obj.faculty;
	this->rooms = obj.rooms;
}
Dormitory::~Dormitory()
{
}
string Dormitory::getFullAddressWithInstitutionName() const
{
	bool noDataDefined = this->street.length() == 0
		&& this->buildingNo.length() == 0
		&& this->faculty.getInstitute().length() == 0;
	if (noDataDefined)
	{
		throw "Must define street , buildingNo and faculty.institute first";
	}

	string ret = "Street: " + this->street + ", No: " + this->buildingNo + ". Institution: " + this->faculty.getInstitute();
	return ret;
}
double Dormitory::getAverageOccupancy() const 
{
	if (rooms.size() == 0) 
	{
		throw "Must define rooms first";
	}
	int totalCapacity = 0;
	int totalOccupied = 0;
	for (unsigned int i = 0; i < rooms.size(); i++) 
	{
		totalCapacity = totalCapacity + rooms.at(i).getCapacity();
		totalOccupied = totalOccupied + rooms.at(i).getOccupied();
	}
	return (double (totalOccupied) / (double)totalCapacity) * 100;

}
Dormitory::operator double() const
{
	return this->getAverageOccupancy();
}
Dormitory& Dormitory::operator =(const Dormitory& obj)
{
	if (this == &obj) {
		return (*this);
	}
	this->~Dormitory();
	this->street = obj.street;
	this->buildingNo = obj.buildingNo;
	this->faculty = obj.faculty;
	this->rooms = obj.rooms;
	return *this;
}
void Dormitory::setFaculty(Faculty faculty)
{
	this->faculty = faculty;
}
void Dormitory::setStreet(string street) 
{
	this->street = street;
}
void Dormitory::setBuildingNo(string buildingNo) 
{
	this->buildingNo = buildingNo;
}
void Dormitory::setRooms(vector<Room> rooms) 
{
	this->rooms = rooms;
}
vector<Room>& Dormitory::getRooms()  
{
	return rooms;
}
Room enterRoom()
{
	int no = getNumberFromConsole("Please input room No (1...1000): ", 1, 1000);
	int capacity = getNumberFromConsole("Please input room capacity (1...5): ", 1, 5);
	string msg = "Please input how many students are already living in the room (0..." + to_string(capacity) +"): ";
	int occupied = getNumberFromConsole(msg, 0, capacity);
	Room room = Room(no, capacity, occupied);
	return room;
}
Room* Dormitory::getByRoomNo(Room room)
{
	for (unsigned int i = 0; i < rooms.size(); i++)
	{
		Room currentRoom = rooms.at(i);
		if (currentRoom == room) 
		{
			return &currentRoom;
		}
	}
	return nullptr;
}
Room& Dormitory::getByRoomNo(int roomNo)
{
	for (unsigned int i = 0; i < rooms.size(); i++)
	{
		if (rooms.at(i).getRoomNo() == roomNo)
		{
			return rooms.at(i);
		}
	}
}
bool Dormitory::addRoom(Room roomToAdd) 
{
	Room *room = getByRoomNo(roomToAdd);
	if (room != nullptr) 
	{
		return false;
	}
	else
	{
		rooms.push_back(roomToAdd);
	}
	return true;
}
void enterRooms(istream& in, Dormitory& dormitory, int roomsToEnter)
{
	vector<Room> rooms;
	int roomsEntered = 0;
	do 
	{
		Room roomToAdd = enterRoom();
		bool isRoomAdded = dormitory + roomToAdd;
		if (!isRoomAdded) 
		{
			cout << "Room with this number already exists in this dormitory. Try again" << endl;
		}
		else 
		{
			roomsEntered++;
		}
		
	} while (roomsEntered < roomsToEnter);
}
istream& operator >>(istream& in, Dormitory& dormitory)
{
	string instName, facultyName, streetName, buildNo;
	instName = getStrFromConsole("Please input institute name: ");
	facultyName = getStrFromConsole("Please input faculty name: ");
	int cnt = getNumberFromConsole("Please input students count (100...1000): ", 100, 10000);
	Faculty faculty = Faculty(instName, facultyName, cnt);
	dormitory.setFaculty(faculty);
	streetName = getStrFromConsole("Please input dormitory street name: ");
	buildNo = getStrFromConsole("Please input dormitory building No: ");
	dormitory.setStreet(streetName);
	dormitory.setBuildingNo(buildNo);
	cnt = getNumberFromConsole("Please input number of rooms to enter manually (1...6): ", 1, 6);
	enterRooms(in, dormitory, cnt);
	return in;
}
ostream& operator <<(ostream& out, Dormitory& dormitory)
{
	out << dormitory.getFullAddressWithInstitutionName() << endl;
	out << "Total amount of rooms in dormitory: " << to_string(dormitory.getRooms().size()) << endl;
	out << "Average dormitory load: " << (double)dormitory << "%" << endl;
	return out;
}
bool Dormitory::operator +(const Room roomToAdd) 
{
	return addRoom(roomToAdd);
}
Room enterRoomFromConsole()
{
	int no = getNumberFromConsole("Please input room No (1...1000): ", 1, 1000);
	int capacity = getNumberFromConsole("Please input room capacity (1...5): ", 1, 5);
	string msg = "Please input how many students are already living in the room (0..." + to_string(capacity) + "): ";
	int occupied = getNumberFromConsole(msg, 0, capacity);
	Room room = Room(no, capacity, occupied);
	return room;
}
void Dormitory::enterRoom()
{
	bool roomAdded = false;
	do
	{
		clearScreen();
		Room roomToAdd = enterRoomFromConsole();
		bool isRoomAdded = this->addRoom(roomToAdd);
		if (!isRoomAdded)
		{
			cout << "Room with this number already exists in this dormitory. Try again." << endl;
			system("pause");
		}
		else
		{
			roomAdded = true;
		}

	} while (!roomAdded);
}
vector<int> Dormitory::listRoomNumbers() const
{
	vector<int> nums;
	for (unsigned int i = 0; i < rooms.size(); i++) 
	{
		nums.push_back(rooms.at(i).getRoomNo());
	}
	return nums;
}
Room* Dormitory::chooseRoom(string msg)
{
	Room* chosenRoom;
	do
	{
		clearScreen();
		vector<int> nums = listRoomNumbers();
		string numsStr;
		for (unsigned int i = 0; i < nums.size(); i++)
		{
			if (i != 0)
			{
				numsStr = numsStr + " ";
			}
			numsStr = numsStr + to_string(nums.at(i));
		}
		cout << "Avaiable rooms: " + numsStr << endl;
		cout << msg;
		int num;
		cin >> num;
		Room toFind;
		toFind.setRoomNo(num);
		chosenRoom = getByRoomNo(toFind);
		if (chosenRoom == nullptr)
		{
			cout << "No room with chosen number is avaibable" << endl;
			system("pause");
		}
	} while (chosenRoom == nullptr);
	return chosenRoom;
}
void Dormitory::addStudents()
{
	Room* choosen = chooseRoom("Choose room No to add students to : ");
	Room roomSelected = *choosen;
	clearScreen();
	cout << roomSelected;
	int max = roomSelected.getCapacity() - roomSelected.getOccupied();
	if (max == 0)
	{
		cout << "This room has no space left" << endl;
	}
	else
	{
		int no = getNumberFromConsole("How many students to add (1..." + to_string(max) + "): ", 1, max);
		Room& roomToUpdate = getByRoomNo(roomSelected.getRoomNo());
		roomToUpdate.addOccupant(no);
	}
	system("pause");
}
void Dormitory::removeStudents()
{
	Room* choosen = chooseRoom("Choose room No to remove students from : ");
	Room roomSelected = *choosen;
	clearScreen();
	cout << roomSelected;
	int max = roomSelected.getOccupied();
	if (max == 0)
	{
		cout << "This room is empty already" << endl;
	}
	else
	{
		int no = getNumberFromConsole("How many students to remove (1..." + to_string(max) + "): ", 1, max);
		Room& roomToUpdate = getByRoomNo(roomSelected.getRoomNo());
		roomToUpdate.removeOccupant(no);
	}
	system("pause");
}
void Dormitory::printAvailableRooms()
{
	vector<Room> rooms = getRooms();
	clearScreen();
	int roomsWithFreeSpace = 0;
	for (unsigned int i = 0; i < rooms.size(); i++) 
	{
		Room current = rooms.at(i);
		if (current.getCapacity() > current.getOccupied()) 
		{
			cout << "Room No: " << rooms.at(i).getRoomNo() << "; Total/Available: "
				<< current.getCapacity() << "/"
				<< current.getCapacity() - current.getOccupied() << endl;
			roomsWithFreeSpace++;
		}
	}
	if (roomsWithFreeSpace == 0)
	{
		cout << "Dormitory is fully booked. There are no free places left." << endl;
	}
	system("pause");
}
void Dormitory::printInstituteStatistics()
{
	vector<Room> rooms = getRooms();
	clearScreen();
	int totalStudentsInUnstitute = this->faculty.getStudentCount();
	int totalStudentsInDormitory = 0;
	for (unsigned int i = 0; i < rooms.size(); i++)
	{
		totalStudentsInDormitory += rooms.at(i).getOccupied();
	}
	cout << "Living in dormitory: " << (double(totalStudentsInDormitory) / (double)totalStudentsInUnstitute) * 100 << "% of all strudents"  << endl;
	system("pause");
}