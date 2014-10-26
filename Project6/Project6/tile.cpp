#include "tile.h"

Tile::Tile(int idNum, int xCoord, int yCoord, int floor) : Location(idNum,xCoord,yCoord), 
	floor_id(floor){

}

void Tile::createArray(){
	roomLayout = new char*[TILE_SIZE];
	for(int i = 0; i < TILE_SIZE;i++){
		roomLayout[i] = new char[TILE_SIZE];
	}
}

char*** Tile::draw(){
	char*** layout = &roomLayout;
	return layout;
}