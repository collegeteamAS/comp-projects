/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	2014-10-30
//*/
//#include <iostream> //debug
#include "floor.h"
#include "location.h"
#include "tile.h"
#include "tile_stairs.h"
//#include "coordlist.h"

Floor::Floor(int idNum) : 
	id(idNum),
	floor(0),
	map(0),
	upStairs(0),
	scoreCounter(0),
	mineCounter(10),
	mineCounterTally(0),
	scoreRoom(false),
	numberOfCreatedRooms(0),
	downStairs(0),
	mapHeight(Tile::TILE_HEIGHT*(MAP_TILES_VISIBLE*2+1)),
	mapWidth(Tile::TILE_WIDTH*(MAP_TILES_VISIBLE*2+1)),
	stairCounter(0){
	createFloor();
	createMap();
}

Floor::~Floor(){
	deleteFloor();
	deleteMap();
}

// ==== private methods ==== 

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
				drawRoom(xRoom, yRoom, i, k, Tile::EMPTY_SPACE);
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
	if(!isValidRoom(x,y)){
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
			if(map[i][k] != Tile::EMPTY_SPACE){
				map[i][k] = Tile::EMPTY_SPACE;
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

// ==== public methods ====

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
			map[i][k] = Tile::EMPTY_SPACE;
		}
	}
}

Location* Floor::createStairs(int idNum, int x, int y, bool isUp){
	StairsTile* stairs = new StairsTile(idNum,x,y,id,isUp);
	Location* loc = &(*stairs); // can we set base pointers = to derived pointers?
	if(isUp){
		upStairs = stairs;
	}
	else{
		downStairs = stairs;
	}
	setLoc(loc,x,y);
	return loc;
}

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

int Floor::getMineCount(){
	if(mineCounterTally == 10){
		mineCounterTally = 0;
		if(mineCounter < 50){
			mineCounter += 5;
		}
	}
	mineCounterTally++;
	return mineCounter;
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

int Floor::getNumberOfCreatedRooms(){
	return numberOfCreatedRooms;
}

int Floor::getScoreCounter(){
	return scoreCounter++;
}

int Floor::getStairCount(){
	return stairCounter++;
}

StairsTile* Floor::getStairsDown(){
	return downStairs;
}

StairsTile* Floor::getStairsUp(){
	return upStairs;
}

bool Floor::hasStairsDown(){
	return downStairs != 0;
}

bool Floor::hasStairsUp(){
	return upStairs != 0;
}

bool Floor::isScoreRoomHere(){
	return scoreRoom;
}

bool Floor::isValidRoom(int x, int y){
	if(x < 0 || y < 0 || x >= FLOOR_HEIGHT || y >= FLOOR_WIDTH || floor[x][y] == 0){
		return false;
	}
	return true;
}

void Floor::setID(int idNum){
	id = idNum;
}

void Floor::setLoc(Location* loc, int x, int y){
	floor[x][y] = loc;
	numberOfCreatedRooms++;
}

void Floor::set_room_doors(int x, int y, bool value){
	floor[x][y]->set_east_door(value);
	floor[x][y]->set_north_door(value);
	floor[x][y]->set_south_door(value);
	floor[x][y]->set_west_door(value);
}

void Floor::setScoreRoomHere(bool value){
	scoreRoom = value;
}
/*// useful, but we dont need anymore
void Floor::syncDoors(int x, int y){
	Location* thisRoom = floor[x][y];
	Location* checkRoom;
	if(isValidRoom(x,y-1)){ // checks room west of this room
		checkRoom = floor[x][y-1];
		if(checkRoom->get_east_door() != thisRoom->get_west_door()){
			checkRoom->set_east_door(false);
			thisRoom->set_west_door(false);
		}
	}
	if(isValidRoom(x-1,y)){ // checks room north of this room
		checkRoom = floor[x-1][y];
		if(checkRoom->get_south_door() != thisRoom->get_north_door()){
			checkRoom->set_south_door(false);
			thisRoom->set_north_door(false);
		}
	}
	if(isValidRoom(x,y+1)){ // checks room east of this room
		checkRoom = floor[x][y+1];
		if(checkRoom->get_west_door() != thisRoom->get_east_door()){
			checkRoom->set_west_door(false);
			thisRoom->set_east_door(false);
		}
	}
	if(isValidRoom(x+1,y)){ // checks room south of this room
		checkRoom = floor[x+1][y];
		if(checkRoom->get_north_door() != thisRoom->get_south_door()){
			checkRoom->set_north_door(false);
			thisRoom->set_south_door(false);
		}
	}
}
//*/