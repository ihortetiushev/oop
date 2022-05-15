#include <iostream>
#include <string>
#include "room.h";
#include "utils.h"


Room::Room()
{
}
Room::Room(int roomNo, int capacity, int occupied)
{
	this->roomNo = roomNo;
	this->capacity = capacity;
	this->occupied = occupied;
}
Room::Room(const Room& obj)
{
	this->roomNo = obj.roomNo;
	this->capacity = obj.capacity;
	this->occupied = obj.occupied;
}
Room::~Room()
{
}
bool Room::operator == (Room& room) const
{
	if (this == &room)
	{
		return true;
	}
	if (this->roomNo == room.roomNo)
	{
		return true;
	}
	return false;
}
int Room::getCapacity() const 
{
	return capacity;
}
int Room::getOccupied() const 
{
	return occupied;
}
int Room::getRoomNo() const
{
	return roomNo;
}
void Room::setCapacity(int capacity) 
{
	this->capacity = capacity;
}
void Room::setOccupied(int occupied)
{
	this->occupied = occupied;
}
void Room::setRoomNo(int roomNo) 
{
	this->roomNo = roomNo;
}

ostream& operator <<(ostream& out, Room& room)
{
	out << "Room No: " << to_string(room.getRoomNo()) << endl;
	out << "Capacity: " << to_string(room.getCapacity()) << endl;
	out << "Occupied: " << to_string(room.getOccupied()) << endl;
	return out;
}
bool Room::addOccupant(int cnt) 
{
	int current = getOccupied();
	current += cnt;
	if ( current <= getCapacity())
	{
		setOccupied(current);
		return true;
	}
	else 
	{
		return false;
	}
}
bool Room::removeOccupant(int cnt)
{
	int current = getOccupied();
	current -= cnt;
	if (current <= getCapacity())
	{
		setOccupied(current);
		return true;
	}
	else
	{
		return false;
	}
}
