#include <string>
#include <iostream>
#include "player.h"
#include "location.h"
#include "crystal.h"

using namespace std;


Crystal::Crystal(char s) : Location(s) 
{			
taken = false; 
}

Crystal::Crystal() : Location()
{
	taken = false;
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
	if(!visited)
	{
		visited = true;
		cout<< "some sort of crystal.";
	}

	return 1;
}

