//FileName:		enemy.cpp
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the methods for the Enemy class

#include "enemy.h"
#include "location.h"

Enemy::Enemy(char s, int h)
	: Location(s)
{
	health = h;
}

int Enemy::visit(Player &p)
{
	return 1;  //NOTE: The Enemy version of this method is not used for this lab activity
}  

int Enemy::attack()
{
	return rand()%4+1;
}