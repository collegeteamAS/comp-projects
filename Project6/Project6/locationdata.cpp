
/*
Andre Allan Ponce
a_ponce2@u.pacific.edu
*/
// #include <iostream> // debug

//#include "location.h"
#include "tile.h"
#include "locationdata.h"


// @author Andre Allan Ponce
LocationData::LocationData() : 
	data(), 
	size(0){

}

LocationData::LocationData(int amount) :
	data(amount),
	size(amount){

}

// @author Andre Allan Ponce
void LocationData::createMaps(int amount){
	data(amount);
	size = amount;
}

// @author Andre Allan Ponce
// number of elements in keys must match size
void LocationData::deleteMaps(int* keys){
	if(size > 0){
		for(int i = 0; i < size; i++){
			int id = keys[i];
			for(int k = 0; k < Tile::TILE_HEIGHT ; k++){
				delete [] data.at(id)[k];
			}
			delete [] data.at(id);
		}
	}
}

// @author Andre Allan Ponce
void LocationData::fillRoom(int id, int rows, int cols, char*** room){
	char** thisRoom = new char*[rows];
	for(int i = 0; i < rows; i++){
		thisRoom[i] = new char[cols];
		for(int k = 0; k < cols; k++){
			thisRoom[i][k] = (*room)[i][k];
			//std::cout << thisRoom[i][k] << " = " << room[i][k] << "\n";
		}
	}
	data.emplace(id, thisRoom);
	size++;
}

/* 
	@author Andre Allan Ponce
	@param col - the column to search
	@param room - the 2d array of chars that represent room
	@param lim - the amount of rows
	@return the row number that the door is on (door is ' '), -1 if door doesnt exist

int RoomData::findDoorOnCol(int id, int col, char** room){
	for(int i = 0; i < roomSizes.at(id)[DIMENSION_ROW]; i++){
		if(room[i][col] == Location::EMPTY_SPACE){
			return i;
		}
	}
	return -1;
}

// @author Andre Allan Ponce
int RoomData::findDoorOnRow(int id, int row, char** room){
	for(int i = 0; i < roomSizes.at(id)[DIMENSION_COL]; i++){
		if(room[row][i] == Location::EMPTY_SPACE){
			return i;
		}
	}
	return -1;
}

// @author Andre Allan Ponce
// {left, up, right, down} 
void RoomData::findDoors(int id, int rows, int cols, char** room){
	int* doors = new int[4];
	doors[DOOR_LEFT] = findDoorOnCol(id, 0, room);
	doors[DOOR_UP] = findDoorOnRow(id, 0, room);
	doors[DOOR_RIGHT] = findDoorOnCol(id, cols-1, room);
	doors[DOOR_DOWN] = findDoorOnRow(id, rows-1, room);
	doorSpots.emplace(id, doors);
}
//*/
// @author Andre Allan Ponce
int LocationData::getSize(){
	return size;
}

// @author Andre Allan Ponce
/*
int RoomData::retrieveDoorSpot(int id, int door){
	return doorSpots.at(id)[door];
}
//*/
// @author Andre Allan Ponce
char*** LocationData::retrieveRoom(int id){
	return &data.at(id);
}
/*
// @author Andre Allan Ponce
int LocationD::retrieveRoomSize(int id, int dimension){
	return roomSizes.at(id)[dimension];
}
//*/

// @author Andre Allan Ponce
void LocationData::setSize(int num){
	size = num;
}