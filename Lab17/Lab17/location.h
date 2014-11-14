//FileName:		location.h
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the header for the location class

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include "player.h"
using namespace std;

class Location
{
	protected:
		bool visited;
		char symbol;

	public:
		Location(char s = ' ') {symbol = s; visited = false;}

		void setVisited(bool v) {visited = v;}
		void setSymbol(char s) {symbol = s;}

		bool getVisited() {return visited;}
		char getSymbol() {return symbol;}

		virtual void draw() {if (visited) cout << symbol; else cout << ".";}
		virtual int visit(Player &p) {visited = true; return 1;}
};

#endif