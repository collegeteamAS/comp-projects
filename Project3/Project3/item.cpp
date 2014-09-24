/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Item class, for all the items
	Steve Suh
	h_suh@u.pacific.edu
*/
#include <iostream>
#include <string>
#include <random>
#include "item.h"
#include "location.h"
#include "player.h"
// Steve Suh
Item::Item(): symbol(NULL), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1)
{
	keyAcheived = false;
	description = "";
}

// Steve Suh
Item::Item(char sym) : symbol(sym), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1)
{
	keyAcheived = false;
	description = "";
}

int Item::getItemLocX()
{
	return xRoom;
}

int Item::getItemLocY()
{
	return yRoom;
}

char Item::getSymbol()
{
	return symbol;
}

//steve suh
void Item::action()
{
	std::cout << description;
}
