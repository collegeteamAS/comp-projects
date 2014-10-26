
#ifndef _TILE_H_INCLUDED_
#define _TILE_H_INCLUDED_

#include "location.h"

class Tile : public Location{
private:
	// just in case
	int floor_id;

public:
	enum Contsants{
		//EMPTY_SPACE = ' '
		TILE_SIZE = 5 // size of a tile (for the map)
	};

	Tile(int idNum, int xCoord, int yCoord, int floor);

	virtual void createArray();
	virtual char*** draw();

	int get_floor_id();

};

#endif