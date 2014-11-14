//FileName:		VGcrystal.h
//Programmer:	Dan Cliburn
//Date:			4/22/2014
//Purpose:		This file defines the header for the VGcrystal class

#ifndef VGCRYSTAL_H
#define VGCRYSTAL_H

#include "crystal.h"

class VGcrystal : public Crystal
{
	public:
		VGcrystal(char symbol);

		int visit(Player &p);
		void draw();
}; //Do NOT forget this semicolon
#endif