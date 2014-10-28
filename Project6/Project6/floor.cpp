#include "floor.h"
#include "location.h"
#include "tile.h"

Floor::Floor(int idNum) : id(idNum){
	createFloor();
}

void Floor::createFloor(){
	floor = new Location**[FLOOR_HEIGHT];
	for(int i = 0; i < FLOOR_HEIGHT; i++){
		floor[i] = new Location*[FLOOR_WIDTH];
		for(int k = 0; k < FLOOR_WIDTH; k++){
			floor[i][k] = 0;
		}
	}
}

void Floor::createMap(int size){
	mapSize = size;
	map = new char*[mapSize];
	for(int i = 0; i < mapSize; i++){
		map[i] = new char[mapSize];
	}
}

int Floor::getID(){
	return id;
}

Location* Floor::getLoc(int x, int y){
	return floor[x][y];
}

std::string Floor::getMap(){
	std::string mapStr = "";
	for(int i = 0; i < mapSize;i++){
		for(int k = 0; k < mapSize;k++){
			mapStr += map[i][k];
		}
		mapStr+="\n";
	}
	return mapStr;
}

std::string Floor::getNewMap(int x, int y, char sym){
	drawMap(x,y,sym);
	return getMap();
}

void Floor::drawMap(int x, int y, char sym){
	int xRoom = 0;
	int yRoom = 0;
	for(int i = x-MAP_TILES_VISIBLE; i <= x+MAP_TILES_VISIBLE; i++){
		for(int k = y-MAP_TILES_VISIBLE; k < y+MAP_TILES_VISIBLE;k++){
			if(i == x && k == y){
				drawRoom(xRoom,yRoom,i,k,sym);
			}
			else{
				drawRoom(xRoom, yRoom, i, k, ROOM_BLANK);
			}
			yRoom += Tile::TILE_WIDTH-1;
		}
		xRoom += Tile::TILE_HEIGHT-1;
		yRoom = 0;
	}
}

void Floor::drawRoom(int startX, int startY, int x, int y, char sym){
	if(x < 0 || y < 0){
		drawRoomBlank(startX,startY);
	}
	else{
		char*** room = floor[x][y]->draw();
		for(int i = startX; i < startX+Tile::TILE_HEIGHT; i++){
			for(int k = startY; k < startY+Tile::TILE_WIDTH; k++){
				if(startX-i == Tile::TILE_HEIGHT/2 && startY-k == Tile::TILE_WIDTH/2){
					map[i][k] = sym;
				}
				else{
					map[i][k] = (*room)[startX-i][startY-k];
				}
			}
		}
	}
}

void Floor::drawRoomBlank(int startX, int startY){
	for(int i = startX; i < startX+Tile::TILE_HEIGHT; i++){
		for(int k = startY; k < startY+Tile::TILE_WIDTH; k++){
			map[i][k] = ROOM_BLANK;
		}
	}
}

void Floor::setID(int idNum){
	id = idNum;
}

void Floor::setLoc(Location* loc, int x, int y){
	floor[x][y] = loc;
}

void Floor::set_room_doors(int x, int y, bool value){
	floor[x][y]->set_east_door(value);
	floor[x][y]->set_north_door(value);
	floor[x][y]->set_south_door(value);
	floor[x][y]->set_west_door(value);
}