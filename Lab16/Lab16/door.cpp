/*//
	Andre Allan Ponce
//*/

#include "door.h"

Door::Door(char symbol) : Location(symbol){

}

void Door::draw()
{
	if (visited == true)
		std::cout << symbol;
	else
		std::cout << ".";
}

int Door::visit(Player &p)
{
	if (visited == false)
	{
		std::cout << MenuText::GAME_DOOR_FOUND << "\n";
	}
	visited = true;
	return 1;
}