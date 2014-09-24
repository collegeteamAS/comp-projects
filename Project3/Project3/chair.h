/*
Steve Suh
h_suh@u.pacific.edu
*/
#ifndef _CHAIR_H_INCLUDED_
#define _CHAIR_H_INCLUDED_

#include "item.h"

class Chair:public Item
{
	private:

	public:
		Chair(char sym, int idNum);
};

#endif