/*//
	Andre Allan Ponce
	Door
//*/

#ifndef _VGDOOR_H_INCLUDED_
#define _VGDOOR_H_INCLUDED_

#include "door.h"

class VGdoor : public Door{
public:
	VGdoor(char symbol);

	virtual int visit(Player& p);
	virtual void draw();
};

#endif