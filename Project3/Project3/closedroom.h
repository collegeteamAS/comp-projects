/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
*/

#ifndef _CLOSEDROOM_H_INCLUDED_
#define _CLOSEDROOM_H_INCLUDED_

#include "location.h"

class ClosedRoom : public Location{

public:
	ClosedRoom();
	ClosedRoom(int idNum, int xCoord, int yCoord, int h, int w);
};

#endif