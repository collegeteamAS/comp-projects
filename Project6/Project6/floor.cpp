#include "floor.h"
#include "location.h"

Floor::Floor(int idNum) : id(idNum){
	createFloor();
}

void Floor::createFloor(){
	floor = new Location**[FLOOR_WIDTH];
	for(int i = 0; i < FLOOR_WIDTH; i++){
		floor[i] = new Location*[FLOOR_HEIGHT];
		for(int k = 0; k < FLOOR_HEIGHT; k++){
			floor[i][k] = 0;
		}
	}
}

int Floor::getID(){
	return id;
}

Location* Floor::getLoc(int x, int y){
	return floor[x][y];
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