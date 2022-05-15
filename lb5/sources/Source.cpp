#include <iostream>
#include <string>
#include "dormitory.h"
#include "utils.h"


using namespace std;

const int EXIT_MENU = 6;
void printDormitoryState(Dormitory dormitory)
{
	cout << "Dormitory:" << endl;
	cout << dormitory;
}
void printMenu() 
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "1. Add room to the dormitory" << endl;
	cout << "2. Add student the the room" << endl;
	cout << "3. Remove students from the room" << endl;
	cout << "4. Free rooms available" << endl;
	cout << "5. % of students living in the dormitory" << endl;
	cout << "6. Exit" << endl;
}
int main()
{
	Dormitory dormitory;
	cin >> dormitory;
	int choice;
	do 
	{
		clearScreen();
		printDormitoryState(dormitory);
		printMenu();
		cout << "Make your choice! ";
		cin >> choice;
		switch (choice) 
		{
			case 1: dormitory.enterRoom(); break;
			case 2:	dormitory.addStudents(); break;
			case 3:	dormitory.removeStudents(); break;
			case 4:	dormitory.printAvailableRooms(); break;
			case 5:	dormitory.printInstituteStatistics(); break;
		}
	} while (choice != EXIT_MENU);
}

