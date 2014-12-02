/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
//*/

#include "tile_stairs.h"

StairsTile::StairsTile(int idNum, int xCoord, int yCoord, int floor, bool isUp) : Tile(idNum,xCoord,yCoord,floor,EMPTY_SPACE),
	connectedStairs(0){
	changeStairs(isUp);
}

// ==== protected methods ====

void StairsTile::changeStairs(bool isUp){
	if(isUp){
		symbol = STAIRS_UP_CHAR;
	}
	else{
		symbol = STAIRS_DOWN_CHAR;
	}
}

// ==== public methods ====

void StairsTile::action(Player* p){
	// add message to player
}

void StairsTile::createNewArray(char*** room){
	Tile::createNewArray(room);
	roomLayout[STAIRS_X][STAIRS_Y] = symbol;
}

void StairsTile::examine(Player* p){
	// move player up or down a floor
	// add message to player if we cant do that
}

int StairsTile::getNextFloor(){
	if(connectedStairs == 0){
		return -1;
	}
	else{
		return connectedStairs->getFloorID();
	}
}

void StairsTile::setNextFloor(StairsTile* next){
	connectedStairs = next;
}