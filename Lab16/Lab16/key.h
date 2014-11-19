
#ifndef _KEY_H_INCLUDED_
#define _KEY_H_INCLUDED_
//author steve suh
#include "location.h"

class Key: public Location 
{

protected:
	bool taken;

public:
	Key(char symbol = 'k');

	virtual int visit(Player& p) = 0;
	virtual void draw() = 0;
};

#endif