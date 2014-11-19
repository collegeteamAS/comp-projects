/*//
	Andre Allan Ponce
//*/

#include "door.h"

Door::Door(char symbol) : Location(symbol){

}

void Door::draw()
{
	if (visited == true)
		cout << symbol;
	else
		cout << ".";
}

int Door::visit(Player &p)
{
	if (visited == false)
	{
		cout << "ya found the door!\n";
	}
	visited = true;
	return 1;
}