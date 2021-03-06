/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
*/

#ifndef _ROOMDATA_H_INCLUDED_
#define _ROOMDATA_H_INCLUDED_

#include <unordered_map>

class RoomData{
private:
	std::unordered_map<int,char**> data; // HashMaps all over again!
	std::unordered_map<int, int*> doorSpots; // left, up, right, down
	std::unordered_map<int, int*> roomSizes; // so we can delete the arrays efficiently ( row, col)
	int size;

	// private methods
	int findDoorOnCol(int id, int col, char** room);
	int findDoorOnRow(int id, int row, char** room);
	void findDoors(int id, int rows, int cols, char** room); // finds 'doors' which are just empty spaces

public:
	// enums are better for constants (java enums were not as great, though)
	enum Constants{
		// Room IDS
		ROOM = 0,

		// closed rooms
		ROOM_ATTIC = 1,
		ROOM_GARAGE = 9,
		ROOM_BATHROOM = 3,

		// closet rooms
		ROOM_BASEMENT = 2,
		ROOM_BEDROOM = 4,

		// open rooms
		ROOM_HALLWAY = 5,
		ROOM_HALLWAY_BLOODY = 6,
		ROOM_HALLWAY_DARK = 7,
		ROOM_DININGROOM = 8,
		ROOM_KITCHEN = 10,
		ROOM_LIVINGROOM = 11,

		// dimension IDS (for roomsize)
		DIMENSION_ROW = 0,
		DIMENSION_COL = 1,

		// door IDS
		DOOR_LEFT = 0,
		DOOR_UP = 1,
		DOOR_RIGHT = 2,
		DOOR_DOWN = 3
	};

	RoomData();

	void createMaps(int amount); // not sure if we need this
	void deleteMaps(int* keys);
	void fillRoom(int id, int rows, int cols, char** room);

	int getSize();

	int retrieveDoorSpot(int id, int door); 
	char** retrieveRoom(int id);
	int retrieveRoomSize(int id, int dimension); // 0 for rows or height, 1 is cols or width

	void setSize(int num);
};

#endif