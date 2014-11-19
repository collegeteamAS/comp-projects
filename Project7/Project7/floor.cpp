/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	2014-10-30
//*/
//#include <iostream> //debug
#include "floor.h"
#include "location.h"
#include "tile.h"
#include "coordlist.h"

Floor::Floor(int idNum) : 
	id(idNum),
	floor(0),
	map(0),
	mapHeight(Tile::TILE_HEIGHT*(MAP_TILES_VISIBLE*2+1)),
	mapWidth(Tile::TILE_WIDTH*(MAP_TILES_VISIBLE*2+1)){
	createFloor();
	createMap();
}

Floor::~Floor(){
	deleteFloor();
	deleteMap();
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

void Floor::createMap(){
	//mapSize = size;
	map = new char*[mapHeight];
	for(int i = 0; i < mapHeight; i++){
		map[i] = new char[mapWidth];
		for(int k = 0; k < mapWidth; k++){
			map[i][k] = ROOM_BLANK;
		}
	}
}

void Floor::deleteFloor(){
	if(floor != 0){
		for(int i = 0; i < FLOOR_HEIGHT; i++){
			if(floor[i] != 0){
				for(int k = 0; k < FLOOR_WIDTH; k++){
					delete floor[i][k];
				}
				delete [] floor[i];
			}
		}
		delete [] floor;
	}
}

void Floor::deleteMap(){
	if(map != 0){
		for(int i = 0; i < mapHeight; i++){
			delete [] map[i];
		}
		delete [] map;
	}
}

void Floor::drawMap(int x, int y, char sym){
	int xRoom = 0;
	int yRoom = 0;
	for(int i = x-MAP_TILES_VISIBLE; i <= x+MAP_TILES_VISIBLE; i++){
		for(int k = y-MAP_TILES_VISIBLE; k <= y+MAP_TILES_VISIBLE;k++){
			//std::cout << xRoom << ":" << yRoom << "\n";
			if(i == x && k == y){
				drawRoom(xRoom,yRoom,i,k,sym);
			}
			else{
				drawRoom(xRoom, yRoom, i, k, ROOM_BLANK);
			}
			yRoom += Tile::TILE_WIDTH;
		}
		xRoom += Tile::TILE_HEIGHT;
		yRoom = 0;
	}
}
/*//
void Floor::drawMapPartial(int x, int y, char sym, Coord_List* list){
	int xRoom = 0;
	int yRoom = 0;
	for(int i = x-MAP_TILES_VISIBLE; i <= x+MAP_TILES_VISIBLE; i++){
		for(int k = y-MAP_TILES_VISIBLE; k <= y+MAP_TILES_VISIBLE;k++){
			//std::cout << xRoom << ":" << yRoom << "\n";
			if(i == x && k == y){
				drawRoomPartial(xRoom,yRoom,i,k,sym,list);
			}
			else{
				drawRoomPartial(xRoom, yRoom, i, k, ROOM_BLANK,list);
			}
			yRoom += Tile::TILE_WIDTH;
		}
		xRoom += Tile::TILE_HEIGHT;
		yRoom = 0;
	}
}
//*/
void Floor::drawRoom(int startX, int startY, int x, int y, char sym){
	if(x < 0 || y < 0 || floor[x][y] == 0 || x >= FLOOR_HEIGHT || y >= FLOOR_WIDTH){
		drawRoomBlank(startX,startY);
	}
	else{
		char*** room = floor[x][y]->draw();
		for(int i = startX; i < startX+Tile::TILE_HEIGHT; i++){
			for(int k = startY; k < startY+Tile::TILE_WIDTH; k++){
				if(i-startX == Tile::TILE_HEIGHT/2 && k-startY == Tile::TILE_WIDTH/2){
					map[i][k] = sym;
				}
				else{
					map[i][k] = (*room)[i-startX][k-startY];
				}
			}
		}
	}
}
/*//
void Floor::drawRoomPartial(int startX, int startY, int x, int y, char sym, Coord_List* list){
	if(x < 0 || y < 0 || floor[x][y] == 0 || x >= FLOOR_HEIGHT || y >= FLOOR_WIDTH){
		drawRoomBlankPartial(startX,startY,list);
	}
	else{
		char*** room = floor[x][y]->draw();
		for(int i = startX; i < startX+Tile::TILE_HEIGHT; i++){
			for(int k = startY; k < startY+Tile::TILE_WIDTH; k++){
				if(i-startX == Tile::TILE_HEIGHT/2 && k-startY == Tile::TILE_WIDTH/2){
					if(map[i][k] != sym){
						map[i][k] = sym;
						list->add_node(map[i][k],i,k);
					}
				}
				else{
					if(map[i][k] == (*room)[i-startX][k-startY]){
						map[i][k] = (*room)[i-startX][k-startY];
						list->add_node(map[i][k],i,k);
					}
				}
			}
		}
	}
}
//*/
void Floor::drawRoomBlank(int startX, int startY){
	for(int i = startX; i < startX+Tile::TILE_HEIGHT; i++){
		for(int k = startY; k < startY+Tile::TILE_WIDTH; k++){
			if(map[i][k] != ROOM_BLANK){
				map[i][k] = ROOM_BLANK;
			}
			//std::cout << i << ":" << k <<"\n";
		}
	}
}
/*//
void Floor::drawRoomBlankPartial(int startX, int startY, Coord_List* list){
	for(int i = startX; i < startX+Tile::TILE_HEIGHT; i++){
		for(int k = startY; k < startY+Tile::TILE_WIDTH; k++){
			if(map[i][k] != ROOM_BLANK){
				map[i][k] = ROOM_BLANK;
				list->add_node(map[i][k],i,k);
			}
			//std::cout << i << ":" << k <<"\n";
		}
	}
}
//*/
int Floor::getID(){
	return id;
}

Location* Floor::getLoc(int x, int y){
	return floor[x][y];
}

std::string Floor::getMap(){
	std::string mapStr = "";
	for(int i = 0; i < mapHeight;i++){
		for(int k = 0; k < mapWidth;k++){
			mapStr += map[i][k];
			//std::cout << map[i][k] << ":" << i << "," << k << "\n";
		}
		mapStr += "\n";
	}
	return mapStr;
}

int Floor::getMapSize(){
	return MAP_TILES_VISIBLE;
}

/*//
Coord_List* Floor::getMapPartial(int x, int y, char sym){
	Coord_List* list = new Coord_List();
	drawMapPartial(x,y,sym,list);
	return list;
}
//*/
std::string Floor::getNewMap(int x, int y, char sym){
	drawMap(x,y,sym);
	return getMap();
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