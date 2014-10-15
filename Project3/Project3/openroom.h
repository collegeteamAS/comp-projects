/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
*/

#ifndef _OPENROOM_H_INCLUDED_
#define _OPENROOM_H_INCLUDED

#include "location.h"

class OpenRoom : public Location{

public:
	OpenRoom();
	OpenRoom(int idNum, int xCoord, int yCoord, int h, int w);
};

#endif