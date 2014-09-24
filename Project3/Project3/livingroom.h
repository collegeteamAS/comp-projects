
#ifndef _LIVINGROOM_H_INCLUDED_
#define _LIVINGROOM_H_INCLUDED_

#include "openroom.h"

class LivingRoom : public OpenRoom{
public:
	LivingRoom();
	LivingRoom(int idNum, int xCoord, int yCoord, int h, int w);
};

#endif