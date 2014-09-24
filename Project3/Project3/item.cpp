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
<<<<<<< HEAD
//#include "location.h"

=======
#include "location.h"
#include "player.h"
>>>>>>> 82e96c42889245432fdc5395350a0c76a2f27fc2
// Steve Suh
Item::Item(): symbol(NULL), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1), id(-1)
{
	keyAcheived = false;
}

// Steve Suh
Item::Item(char sym, int idNum) : symbol(sym), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1), id(idNum)
{
	keyAcheived = false;
	
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

<<<<<<< HEAD
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
=======
//steve suh
void Item::action()
{
	std::cout << description;
}
>>>>>>> 82e96c42889245432fdc5395350a0c76a2f27fc2
