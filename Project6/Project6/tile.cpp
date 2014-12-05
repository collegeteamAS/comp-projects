/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	
//*/
#include "tile.h"
#include "player.h"
#include "node.h"
#include "item.h"
#include "key.h"
#include "menutext.h"
#include "linkedList.h"

Tile::Tile(int idNum, int xCoord, int yCoord, int floor, char sym) : Location(idNum,xCoord,yCoord,floor,sym), 
	hasKey(false),
	numKeys(0){
	
}

Tile::~Tile(){
	deleteLayout();
}

// ==== private methods ====

void Tile::deleteLayout(){
	if(roomLayout != 0){
		for(int i = 0; i < Tile::TILE_HEIGHT; i++){
			if(roomLayout[i] != 0){
				delete [] roomLayout[i];
			}
		}
		delete [] roomLayout;
	}
}

// ==== protected methods ====


void Tile::addExistingKey(Item* key){
	int xKey;
	int yKey;
	if(hasKey){
		switch(numKeys){
		case 1:{
			xKey = KEY_X_1;
			yKey = KEY_Y_1;
			break;
		}
		case 2:{
			xKey = KEY_X_2;
			yKey = KEY_Y_2;
			break;
		}
		default:{
			// we shouldnt be going here
			break;
		}
		}
	}
	else{
		hasKey = true;
		xKey = KEY_X_0;
		yKey = KEY_Y_0;
	}
	numKeys++;
	roomLayout[xKey][yKey] = key->getSymbol();
}

void Tile::removeItems(){
	hasKey = false;
	roomLayout[KEY_X_0][KEY_Y_0] = EMPTY_SPACE;
	roomLayout[KEY_X_1][KEY_Y_1] = EMPTY_SPACE;
	roomLayout[KEY_X_2][KEY_Y_2] = EMPTY_SPACE;
	delete items;
	items = new LinkedList();
}

// ==== public methods ====

void Tile::action(Player* p){
	if(!visited){
		if(hasKey){
			p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_KEY_ACTION);
		}
		else{
			p->setMessageIn(Player::MESSAGE_SLOT_ACTION,MenuText::TILE_NO_ACTION);
		}
		visited = true;
	}
}

void Tile::addKey(){
	Node* key = new Node();
	Key* k = new Key();
	key->pointTo(k);
	addItem(key);
}

void Tile::addItem(Node* n){
	if(n->getItem()->getID() == Item::ID_KEY){
		addExistingKey(n->getItem());
		//std::cout << "key making\n";
	}
	Location::addItem(n);
}

void Tile::createNewArray(char*** room){
	roomLayout = new char*[TILE_HEIGHT];
	for(int i = 0; i < TILE_HEIGHT;i++){
		roomLayout[i] = new char[TILE_WIDTH];
		for(int k = 0; k < TILE_WIDTH; k++){
			roomLayout[i][k] = (*room)[i][k];
		}
	}
}

char*** Tile::draw(){
	char*** layout = &roomLayout;
	return layout;
}

void Tile::examine(Player* p){
	if(hasKey){
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_KEY_EXAMINE);
	}
	else{
		p->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::TILE_NOTHING_TO_EXAMINE);
	}
}

Node* Tile::getItem(int id){
	int xKey;
	int yKey;
	switch(numKeys){
	case 3:{
		xKey = KEY_X_2;
		yKey = KEY_Y_2;
		break;
	}
	case 2:{
		xKey = KEY_X_1;
		yKey = KEY_Y_1;
		break;
	}
	case 1:{
		xKey = KEY_X_0;
		yKey = KEY_Y_0;
		hasKey = false;
		break;
	}
	default:{
		// we should never get here
		break;
	}
	}
	numKeys--;
	roomLayout[xKey][yKey] = EMPTY_SPACE;
	return Location::getItem(id);
}
