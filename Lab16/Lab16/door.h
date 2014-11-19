
/*//
	Andre Allan Ponce
//*/

#ifndef _DOOR_H_INCLUDED_
#define _DOOR_H_INCLUDED_

#include "location.h"

class Door : public Location{
public:
	Door(char symbol = 'd');

	virtual int visit(Player& p) = 0;
	virtual void draw() = 0;
};


#endif