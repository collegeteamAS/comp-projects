
/*
Andre Allan Ponce
a_ponce2@u.pacific.edu
*/
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

// @author Andre Allan Ponce
int LocationData::getSize(){
	return size;
}

// @author Andre Allan Ponce
char*** LocationData::retrieveRoom(int id){
	return &data.at(id);
}

// @author Andre Allan Ponce
void LocationData::setSize(int num){
	size = num;
}