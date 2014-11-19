//FileName:		crystal.h
//Programmer:	Dan Cliburn
//Date:			4/22/2014
//Purpose:		This file defines the header for the Crystal class

#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "location.h"

class Crystal : public Location
{
	protected:			//MAKE SURE THIS IS PROTECTED
		bool taken;

	public:
		Crystal(char s = 'c');

		virtual int visit(Player &p);  //MAKE THIS VIRTUAL
		virtual void draw();	//MAKE THIS VIRTUAL
}; //Do NOT forget this semicolon
#endif