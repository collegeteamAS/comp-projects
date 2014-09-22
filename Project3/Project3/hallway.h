
#ifndef _HALLWAY_H_INCLUDED_
#define _HALLWAY_H_INCLUDED_

#include "room.h"

class Hallway : public Room{
public:
	Hallway();
	Hallway(int idNum, int xCoord, int yCoord, int h, int w);

};

#endif