
#ifndef _BASEMENT_H_INCLUDED_
#define _BASEMENT_H_INCLUDED_

//#include "room.h"

class Basement : public Location{
public:
	Basement();
	Basement(int idNum, int xCoord, int yCoord, int h, int w);
};

#endif