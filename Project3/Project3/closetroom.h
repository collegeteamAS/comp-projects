/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
*/

#ifndef _CLOSETROOM_H_INCLUDED_
#define _CLOSETROOM_H_INCLUDED_

#include "location.h"

class ClosetRoom : public Location {

public:
	ClosetRoom();
	ClosetRoom(int idNum, int xCoord, int yCoord, int h, int w);
};

#endif