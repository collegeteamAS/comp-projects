/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu

	2014-12-01
	+creation of the stair tile
//*/
#ifndef _TILE_STAIRS_H_INCLUDED_
#define _TILE_STAIRS_H_INCLUDED_

#include "tile.h"

class StairsTile : public Tile{
protected:
	StairsTile* connectedStairs;
	// stairs point to its corresponding stairs (which should be on another floor)

	void changeStairs(bool isUp);
	/*// changes the stairs oreintation based on the boolean
		@param isUp - true if we are changing the stairs to up, false if down
	//*/

public:
	enum Constants{
		STAIRS_UP_CHAR = 0x2F, // the '/' character 
		STAIRS_DOWN_CHAR = 0x5C, // the '\' character
		STAIRS_X = 3,
		STAIRS_Y = 1
	};
	StairsTile(int idNum, int xCoord, int yCoord, int floor, bool isUp);
	/*//
		when isUp == true, we use stairs up char
		else we use the down char
	//*/

	virtual void action(Player* p);
	virtual void createNewArray(char*** room);
	virtual void examine(Player* p);

	int getNextFloor();
	// @returns -1 if there stairs are not matched

	void setNextFloor(StairsTile* next);
};

#endif