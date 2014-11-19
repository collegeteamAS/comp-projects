//FileName:		crystal.cpp
//Programmer:	Dan Cliburn
//Date:			4/12/2013
//Purpose:		This file defines the methods for the Crystal class

#include "crystal.h"

Crystal::Crystal(char s) 
	: Location(s) //: Location(s) passes the parameter s to the base
{				//class constructor (in this case, Location) 
	taken = false; //initialize class specific attributes here
}


void Crystal::draw()
{
	if (visited == true && taken == false)
		cout << symbol;
	else if (taken == true)
		cout << " ";
	else
		cout << ".";
}

int Crystal::visit(Player &p)
{
	if (taken == false)
	{
		//taken = true;
		cout << "You found a magic crystal" << endl;
	}
	visited = true;
	return 1;
}