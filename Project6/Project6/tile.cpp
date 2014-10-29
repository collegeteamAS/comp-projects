#include "tile.h"

Tile::Tile(int idNum, int xCoord, int yCoord, int floor) : Location(idNum,xCoord,yCoord), 
	floor_id(floor){
	
}

void Tile::createArray(){
	roomLayout = new char*[TILE_HEIGHT];
	for(int i = 0; i < TILE_HEIGHT;i++){
		roomLayout[i] = new char[TILE_WIDTH];
	}
}

char*** Tile::draw(){
	char*** layout = &roomLayout;
	return layout;
}

void Tile::fillArray(char*** room){
	for(int i = 0; i < TILE_HEIGHT; i++){
		for(int k = 0; k < TILE_WIDTH; k++){
			roomLayout[i][k] = (*room)[i][k];
		}
	}
}