/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
//*/

#include "tile_exit.h"

ExitTile::ExitTile(int idNum, int xCoord, int yCoord, char sym) : Tile(idNum,xCoord,yCoord,sym){

}

// ==== public methods ====

void ExitTile::action(Player* p){
	// add message to player
}

void ExitTile::createNewArray(char*** room){
	Tile::createNewArray(room);
	roomLayout[END_GAME_X][END_GAME_Y] = symbol;
}

void ExitTile::examine(Player* p){
	// open exit, end game OR
	// prompt player not enough keys
}