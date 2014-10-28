/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	(20% done by steve)
*/

#ifndef _LOCATION_H_INCLUDED_
#define _LOCATION_H_INCLUDED_

#include <string>

class Location{
protected:
	bool visited;

	int id;
	char** roomLayout; // visualization of the room
	// roomLayout(0,std::vector<char>(0,'0'))

	// rooms with closets have importance
	//bool hasCloset;

	// rooms with only one door are closed
	//bool isClosed;

	// where this location is
	int x; 
	int y;

		// door placement
	bool has_east_door;
	bool has_north_door;
	bool has_south_door;
	bool has_west_door;

public:
	
	Location();
	Location(int idNum, int xCoord, int yCoord);
	//~Room(); this is giving some issues right now

	virtual void createArray() = 0; // height and width should be set, already
	//void deleteArray();
	//bool doesRoomHaveCloset();
	virtual char*** draw() = 0;
	virtual void fillArray(char*** room) = 0; // dont forget to fill the array

	bool get_east_door();
	bool get_north_door();
	bool get_south_door();
	bool get_west_door();

	int getHeight();
	int getRoomID();
	char getSpaceAt(int xCoord, int yCoord);
	int getWidth();

	bool isRoomClosed();
	bool movePlayer(int xOld, int yOld, char player, int xNew, int yNew); // this moves player to new spot (if valid) and updates the array
	void resetSpace(int xSpace, int ySpace, char space);
	void setPlayer(int xPlay, int yPlay, char player);

	//void setRoomCloset(bool value);
	void setRoomID(int idNum);

	void set_east_door(bool value);
	void set_north_door(bool value);
	void set_south_door(bool value);
	void set_west_door(bool value);
};

#endif