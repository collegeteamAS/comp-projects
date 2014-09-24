#include <string>
#include <iostream>
#include "player.h"

using namespace std;

class Location{
protected:
	bool visited;
	char symbol;

public:
	Location();
	Location(char s);
	bool getVisited();
	char getSymbol();

	void setVisited(bool vis);
	void setSymbol(char sym);

	virtual void draw();
	virtual int visit(Player &p);
};