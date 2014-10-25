
#ifndef _TILE_H_INCLUDED_
#define _TILE_H_INCLUDED_

#include "location.h"

class Tile : public Location{
private:
	// just in case
	int floor_id;

public:
	Tile(int idNum, int xCoord, int yCoord, int floor);

	int get_floor_id();

};

#endif