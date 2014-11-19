#include "key.h"

//Author steve suh

Key::Key(char symbol) : Location(symbol), taken(false)
{
	
}

void Key::draw()
{
	if (visited == true && taken == false)
		cout << symbol;
	else if (taken == true)
		cout << " ";
	else
		cout << ".";
}

int Key::visit(Player &p)
{
	if (taken == false)
	{
		//taken = true;
		cout << "ya found a key!\n";
	}
	visited = true;
	return 1;
}
