//FileName:		VGcrystal.h
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the header for the VGcrystal class

#ifndef VGCRYSTAL_H
#define VGCRYSTAL_H

#include "crystal.h"
#include "billboard.h"

class VGcrystal : public Crystal
{
	private:
		Billboard crystal;

	public:
		VGcrystal(char symbol);

		int visit(Player &p);
		void draw();
}; 
#endif