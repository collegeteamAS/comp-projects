//FileName:		VGcrystal.h
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the header for the VGenemy class

#ifndef VGenemy_H
#define VGenemy_H

#include "enemy.h"
#include "billboard.h"

class VGenemy : public Enemy
{
	private:
		Billboard enemy;

	public:
		VGenemy(char symbol);

		int visit(Player &p);
		void draw();
};
#endif