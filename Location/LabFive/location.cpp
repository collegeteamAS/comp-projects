
#include <string>
#include <iostream>
#include "player.h"
#include "location.h"


using namespace std;

Location::Location()
{
	visited = false;
	symbol='n';
}

Location::Location(char s)
{
	visited = false;
	symbol = s;
}

bool Location::getVisited()
{
	return visited;
}

char Location::getSymbol()
{
	return symbol;
}

void Location::setVisited(bool vis)
{
	visited = vis;
}

void Location::setSymbol(char sym)
{
	symbol = sym;
}

void Location::draw()
{
	if(visited)
		cout<< symbol;
	else
		cout<< ".";
}

int Location::visit(Player &p)
{
	visited = true;
	return 1;
}