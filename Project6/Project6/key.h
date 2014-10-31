
#ifndef _KEY_H_INCLUDED_
#define _KEY_H_INCLUDED_
//author steve suh
#include "item.h"

class Key: public Item 
{
private:
	char symbol;//symbol of the item on the printed screen
	int id;

public:
	Key();

};

#endif