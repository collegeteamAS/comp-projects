#include "Item.h"

//Author steve suh

Item::Item()
{
	//symbol = 'd';
	//id = -1 ;
}

void Item::setID(int idNum)
{
	id = idNum;
}

int Item::getID()
{
	return id;
}

void Item::setSymbol(char sym)
{
	symbol = sym;
}

char Item::getSymbol()
{
	return symbol;
}

