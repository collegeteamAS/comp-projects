/*//
	Andre Allan Ponce
	Steven Suh
	-> modified version of Lab16 location.h
//*/

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include "player.h"
#include "menutext.h"


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

		virtual void draw() {if (visited) std::cout << symbol; else std::cout << ".";}
		virtual int visit(Player &p) {visited = true; return 1;}
};

#endif