#pragma once
#include <iostream> 

using namespace std;

class Room
{
private:
	int roomNo = 0;
	int capacity = 1; //by default room can get single person
	int occupied = 0; //and it's free by default
public:
	Room();
	Room(int roomNo, int capacity, int occupied);
	Room(const Room& obj);
	~Room();
	int getCapacity() const;
	int getOccupied() const;
	int getRoomNo() const;
	void setCapacity(int capacity);
	void setOccupied(int occupied);
	void setRoomNo(int roomNo);
	bool addOccupant(int cnt);
	bool removeOccupant(int cnt);
	bool operator == (Room& room) const;
};
//istream& operator >>(istream& in, Room& room);
ostream& operator <<(ostream& in, Room& room);

