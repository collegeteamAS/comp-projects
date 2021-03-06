/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	
//*/
#include "tile.h"
#include "node.h"
#include "item.h"
#include "key.h"

Tile::Tile(int idNum, int xCoord, int yCoord, int floor) : Location(idNum,xCoord,yCoord), 
	floor_id(floor),
	hasKey(false),
	numKeys(0){
	
}

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

int Tile::get_floor_id(){
	return floor_id;
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

void Tile::setFinalRoom(bool value){
	roomLayout[END_GAME_X][END_GAME_Y] = END_GAME_CHAR;
	Location::setFinalRoom(value);
}