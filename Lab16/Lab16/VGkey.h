/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Header for the graphical version of the key
//*/

#ifndef _VGKEY_H_INCLUDED_
#define _VGKEY_H_INCLUDED_

#include "key.h"

class VGkey : public Key{
public:
	VGkey(char symbol);

	virtual int visit(Player& p);
	virtual void draw();
};

#endif