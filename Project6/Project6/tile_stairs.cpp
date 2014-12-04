/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
//*/

#include "tile_stairs.h"
#include "player.h"
#include "menutext.h"

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
	if(!visited){
		p->setMessageIn(Player::MESSAGE_SLOT_ACTION,MenuText::TILE_STAIRS_ACTION);
		visited = true;
	}
	if(hasKey){
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_KEY_ACTION);
	}
}

void StairsTile::createNewArray(char*** room){
	Tile::createNewArray(room);
	roomLayout[STAIRS_X][STAIRS_Y] = symbol;
}

void StairsTile::examine(Player* p){
	p->setCurrentFloor(getNextFloor());
	p->setMessageIn(Player::MESSAGE_SLOT_ACTION,MenuText::TILE_STAIRS_MOVE);
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