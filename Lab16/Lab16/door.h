
/*//
	Andre Allan Ponce
//*/

#ifndef _DOOR_H_INCLUDED_
#define _DOOR_H_INCLUDED_

#include "location.h"

class Door : public Location{
public:
	enum Constants{
		SYMBOL_DOOR = 'd'
	};

	Door(char symbol = SYMBOL_DOOR);

	virtual int visit(Player& p);
	virtual void draw();
};


#endif