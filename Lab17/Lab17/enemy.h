//FileName:		enemy.h
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the header for the Enemy class

#include "location.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Location
{
	protected:
		int health;

	public:
		Enemy(char s = 'e', int h = 1);

		void setHealth(int h) {health = h;}
		int getHealth() {return health;}

		virtual int visit(Player &p);
		virtual void draw() {;}
		
		int attack();
};

#endif