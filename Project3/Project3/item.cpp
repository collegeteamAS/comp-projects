/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Item class, for all the items
	Steve Suh
	h_suh@u.pacific.edu
*/
#include <iostream>
#include <string>
#include "item.h"

// Steve Suh
Item::Item(): symbol(NULL), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1), id(-1)
{
<<<<<<< HEAD
	description = "";
=======
	keyAcheived = false;
>>>>>>> e692805bc743cdf709b3569e29a559e39528d45b
}

// Steve Suh
Item::Item(char sym, int idNum) : symbol(sym), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1), id(idNum)
{
<<<<<<< HEAD
	description = "";
=======
	keyAcheived = false;
	
>>>>>>> e692805bc743cdf709b3569e29a559e39528d45b
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


int Item::getID(){
	return id;
}

std::string Item::getDescription(){
	return descript;
}

void Item::setDescription(std::string desc){
	descript = desc;
}


void Item::action()
{
	
}


