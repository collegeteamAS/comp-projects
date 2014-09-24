
#include <string>
//#include <iostream>
//#include "player.h"
#include "location.h"


using namespace std;

Location::Location() : 
	visited(false), 
	x(-1), 
	y(-1)
{
	
}

Location::Location(int xCoord, int yCoord) : 
	visited(false){

}

bool Location::getVisited()
{
	return visited;
}

// @author Andre Allan Ponce
int Location::getX(){
	return x;
}

// @author Andre Allan Ponce
int Location::getY(){
	return y;
}

void Location::setVisited(bool vis)
{
	visited = vis;
}

/*
std::string Location::draw()
{
	
	if(visited)
		cout<< symbol;
	else
		cout<< ".";
		
}*/
/*
int Location::visit(Player &p)
{
	visited = true;
	return 1;
}
*/
