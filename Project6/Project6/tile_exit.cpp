/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
//*/

#include "tile_exit.h"
#include "player.h"
#include "menutext.h"

ExitTile::ExitTile(int idNum, int xCoord, int yCoord, int floor, char sym) : Tile(idNum,xCoord,yCoord,floor,sym){

}

// ==== public methods ====

void ExitTile::action(Player* p){
	if(!visited){
		p->setMessageIn(Player::MESSAGE_SLOT_ACTION,MenuText::TILE_EXIT_ACTION);
	}
	if(hasKey){
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_KEY_ACTION);
	}
}

void ExitTile::createNewArray(char*** room){
	Tile::createNewArray(room);
	roomLayout[END_GAME_X][END_GAME_Y] = symbol;
}

void ExitTile::examine(Player* p){
	if(numKeys == 3){
		p->setCurrentFloor(Player::IS_AT_END_GAME);
	}
	else{
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_EXIT_NOT_ENOUGH_KEYS);
	}
}