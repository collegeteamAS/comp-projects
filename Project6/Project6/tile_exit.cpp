/*//
	Steve Suh
	h_suh@u.pacific.edu
//*/

#include <sstream>
#include "tile_exit.h"
#include "player.h"
#include "menutext.h"

ExitTile::ExitTile(int idNum, int xCoord, int yCoord, int floor, char sym) : Tile(idNum,xCoord,yCoord,floor,sym),
	locked(false){

}

// ==== public methods ====

void ExitTile::action(Player* p){
	if(!visited){
		p->setMessageIn(Player::MESSAGE_SLOT_ACTION,MenuText::TILE_EXIT_ACTION);
		visited = true;
		if(hasKey){
			p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_KEY_ACTION);
		}
	}
}

void ExitTile::createNewArray(char*** room){
	Tile::createNewArray(room);
	roomLayout[END_GAME_X][END_GAME_Y] = symbol;
}

void ExitTile::examine(Player* p){
	if(locked){
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_EXIT_EXAMINE_LOCK);
	}
	else if(numKeys == 3){
		p->addToScore(SCORE);
		stringstream str;
		str << MenuText::TILE_EXIT_SCORE_PREFIX << SCORE << MenuText::TILE_EXIT_SCORE_SUFFIX;
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,str.str());
		p->setMessageIn(Player::MESSAGE_SLOT_ACTION,MenuText::TILE_EXIT_LOCKING);
		locked = true;
		roomLayout[END_GAME_X][END_GAME_Y] = END_GAME_CHAR_LOCK;
		symbol = END_GAME_CHAR_LOCK;
		removeItems();
	}
	else{
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_EXIT_NOT_ENOUGH_KEYS);
	}
}