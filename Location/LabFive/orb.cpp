#include <string>
#include <iostream>

#include "player.h"
#include "location.h"
#include "orb.h"

using namespace std;


Orb::Orb(char s) : Location(s)
{		
taken = false; 
}

Orb::Orb() : Location()
{
	taken = false;
}

void Orb::draw()
{
	if (visited == true && taken == false)
		cout << symbol;
	else if (taken == true)
		cout << " ";
	else
		cout << ".";
}

int Orb::visit(Player &p)
{
	if(!visited)
	{
		visited = true;
		cout<< "some sort of Orb.";
	}

	return 1;
}

