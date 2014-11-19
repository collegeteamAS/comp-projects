//FileName:		VGcrystal.cpp
//Programmer:	Dan Cliburn
//Date:			4/22/2014
//Purpose:		This file defines the methods for the VGcrystal class

#include "VGcrystal.h"
#include "player.h"
#include "videoGame.h"

VGcrystal::VGcrystal(char symbol) : Crystal(symbol)
{				
	;
}

void VGcrystal::draw()
{
	if (visited == true && taken == false)
	{
		Videogame::renderBitMap( ((int)(symbol)) );
			//This code converts the symbol (a char) to an integer
			//to be used as the texture ID for this type of object
	}
}

int VGcrystal::visit(Player &p)
{
	if (visited == false)
	{
		Videogame::setMessage2("You found a magic crystal");
	}
	visited = true;
	return 1;
}