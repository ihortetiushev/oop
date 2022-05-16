#include <iostream>
#include <string>
#include "dormitory.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

bool compareByAverageOccupancy(const Dormitory& a, const Dormitory& b)
{
	return a.getAverageOccupancy() < b.getAverageOccupancy();
}
int getFreeRoomsAmount(const Dormitory& elem) {
	int count = 0;
	for (auto it : elem.getRooms()) 
	{
		if (it.getOccupied() == 0) 
		{
			count++;
		}
	}
	return count;
}
bool freeRoomsMore4(const Dormitory& dormitory)
{
	return getFreeRoomsAmount(dormitory) > 4;
}
int getBuildingNo(const Dormitory& dormitory)
{
	return dormitory.getBuildingNo(); 
}
int addAverageOccupancy(int res, const Dormitory& dormitory)
{
	return res + dormitory.getAverageOccupancy();
}
bool compareDormitory(const Dormitory& a, const Dormitory& b)
{
	return a.getFullAddressWithInstitutionName() == b.getFullAddressWithInstitutionName();
}
int main()
{
	string filename = "dormitories.txt";
	ifstream fin(filename);
	if (!fin)
	{
		cerr << "File "+ filename +" not found" << endl;
		system("pause");
		return 0;
	}
	vector<Dormitory> dormitories;
	copy(istream_iterator<Dormitory>(fin), istream_iterator<Dormitory>(), back_inserter(dormitories));
	cout << "Task 1:" << endl;//in from file and out into file
	copy(dormitories.begin(), dormitories.end(), ostream_iterator<Dormitory>(cout, "\n"));
	ofstream fout("result.txt");
	copy(dormitories.begin(), dormitories.end(), ostream_iterator<Dormitory>(fout, "\n"));

	cout << "Task 2:" << endl;//sort 
	cout << "Sort by street address and No: \n";
	std::sort(dormitories.begin(), dormitories.end());
	copy(dormitories.begin(), dormitories.end(), ostream_iterator<Dormitory>(cout, "\n"));
	cout << "Sort by average occupancy:"<< endl;
	std::sort(dormitories.begin(), dormitories.end(), compareByAverageOccupancy);
	copy(dormitories.begin(), dormitories.end(), ostream_iterator<Dormitory>(cout, "\n"));
	
	cout << "Task 3:" << endl;
	vector<Dormitory> more_that_four_free_rooms;
	copy_if(dormitories.begin(), dormitories.end(), back_inserter(more_that_four_free_rooms), freeRoomsMore4);
	copy(more_that_four_free_rooms.begin(), more_that_four_free_rooms.end(), ostream_iterator<Dormitory>(cout, "\n"));

	cout << "Task 4:" << endl;
	vector<int> buildingNumbers;
	transform(more_that_four_free_rooms.begin(), more_that_four_free_rooms.end(), back_inserter(buildingNumbers), getBuildingNo);
	copy(buildingNumbers.begin(), buildingNumbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl << endl;

	cout << "Task 5:" << endl;
    cout << "Amount of records with Building number > given number (110)" << endl;
	int count = count_if(buildingNumbers.begin(), buildingNumbers.end(), bind2nd(not2(less<int>()), 110));
	cout << "count = " << count << endl << endl;

	cout << "Task 6:" << endl;
	int total = accumulate(dormitories.begin(), dormitories.end(), 0, addAverageOccupancy);
	double average = (double) total/ dormitories.size();
	cout << "totalAverageOccupancy = " << average << endl << endl;

	cout << "Task 7:" << endl;
	//can be done useing intersection
	vector<Dormitory> found;
	set_intersection(dormitories.begin(), dormitories.end(),
		more_that_four_free_rooms.begin(), more_that_four_free_rooms.end(),
		std::back_inserter(found));
	copy(found.begin(), found.end(), ostream_iterator<Dormitory>(cout, "\n"));

	system("pause");
	return 0;
}

