
#include <iostream> // debug
#include "room.h"
#include "roomdata.h"

class Room;

// @author Andre Allan Ponce
RoomData::RoomData() : 
	data(), 
	doorSpots(), 
	roomSizes(), 
	size(0){

}

// @author Andre Allan Ponce
void RoomData::createMaps(int amount){
	data(amount);
	doorSpots(amount);
	roomSizes(amount);
	size = amount;
}

// @author Andre Allan Ponce
// number of elements in keys must match size
void RoomData::deleteMaps(int* keys){
	if(size > 0){
		for(int i = 0; i < size; i++){
			int id = keys[i];
			for(int k = 0; k < roomSizes.at(id)[DIMENSION_ROW]; k++){
				char* row = data.at(id)[k];
				delete [] row;
			}
			delete [] data.at(id);
			delete [] doorSpots.at(id);
			delete [] roomSizes.at(id);
		}
	}
}

// @author Andre Allan Ponce
void RoomData::fillRoom(int id, int rows, int cols, char** room){
	char** thisRoom = new char*[rows];
	for(int i = 0; i < rows; i++){
		thisRoom[i] = new char[cols];
		for(int k = 0; k < cols; k++){
			thisRoom[i][k] = room[i][k];
			//std::cout << thisRoom[i][k] << " = " << room[i][k] << "\n";
		}
	}
	data.emplace(id, thisRoom);
	int* sizes = new int[2];
	sizes[DIMENSION_ROW] = rows;
	sizes[DIMENSION_COL] = cols;
	roomSizes.emplace(id,sizes);
	findDoors(id, rows, cols, room);
	size++;
}

/* 
	@author Andre Allan Ponce
	@param col - the column to search
	@param room - the 2d array of chars that represent room
	@param lim - the amount of rows
	@return the row number that the door is on (door is ' '), -1 if door doesnt exist
*/
int RoomData::findDoorOnCol(int id, int col, char** room){
	for(int i = 0; i < roomSizes.at(id)[DIMENSION_ROW]; i++){
		if(room[i][col] == Room::EMPTY_SPACE){
			return i;
		}
	}
	return -1;
}

// @author Andre Allan Ponce
int RoomData::findDoorOnRow(int id, int row, char** room){
	for(int i = 0; i < roomSizes.at(id)[DIMENSION_COL]; i++){
		if(room[row][i] == Room::EMPTY_SPACE){
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

// @author Andre Allan Ponce
int RoomData::getSize(){
	return size;
}

// @author Andre Allan Ponce
int RoomData::retrieveDoorSpot(int id, int door){
	return doorSpots.at(id)[door];
}

// @author Andre Allan Ponce
char** RoomData::retrieveRoom(int id){
	return data.at(id);
}

// @author Andre Allan Ponce
int RoomData::retrieveRoomSize(int id, int dimension){
	return roomSizes.at(id)[dimension];
}

// @author Andre Allan Ponce
void RoomData::setSize(int num){
	size = num;
}