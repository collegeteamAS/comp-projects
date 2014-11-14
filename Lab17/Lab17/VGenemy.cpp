//FileName:		VGenemy.cpp
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the methods for the VGenemy class

#include "VGenemy.h"
#include "player.h"
#include "videoGame.h"

VGenemy::VGenemy(char symbol) : Enemy(symbol)
{				
	enemy.setID( ((int)(symbol)) );
}

void VGenemy::draw()
{
	if (health > 0)
	{
		enemy.draw(0.5);  //The parameter is the the size (ranges from 0.0 to 1.0);
	}
}

int VGenemy::visit(Player &p)
{
	if (health > 0)
	{
		Videogame::setMessage2("You are attacked by an evil balloon!");
		p.setHealth(p.getHealth() - attack());
		health = 0;
	}
	visited = true;
	return 5;  //This number of 5 will indicate that we are in a fight with an enemy
}