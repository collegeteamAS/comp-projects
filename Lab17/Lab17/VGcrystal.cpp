//FileName:		VGcrystal.cpp
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the methods for the VGcrystal class

#include "VGcrystal.h"
#include "player.h"
#include "videoGame.h"

VGcrystal::VGcrystal(char symbol) : Crystal(symbol)
{				
	crystal.setID( ((int)(symbol)) );
}

void VGcrystal::draw()
{
	if (taken == false)
	{
		crystal.draw(0.5, true);  //The parameter is the the size (ranges from 0.0 to 1.0);
	}
}

int VGcrystal::visit(Player &p)
{
	if (visited == false)
	{
		Videogame::setMessage2("You found a magic crystal that increases your health by one.");
		p.setHealth(p.getHealth() + 1);
		taken = true;
	}
	visited = true;
	return 1;
}