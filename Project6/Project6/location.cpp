
/*
Andre Allan Ponce
a_ponce1@u.pacific.edu
Steve Suh
h_suh@u.pacific.edu
*/


#include <string>
#include "location.h"
#include "linkedList.h"


// @author Andre Allan Ponce
Location::Location() : 
	x(-1), 
	y(-1),
	id(-1), 
	items(0),
	roomLayout(0){
	items = new LinkedList();
}

// @author Andre Allan Ponce
Location::Location(int idNum, int xCoord, int yCoord) : 
	x(xCoord), 
	y(yCoord),
	id(idNum),
	items(0),
	roomLayout(0){
	items = new LinkedList();
}

void Location::addItem(Node* n){
	items->add_node(n);
}

// @author Andre Allan Ponce
/*
void Location::createArray(){
	roomLayout = new char*[LOC_SIZE];
	for(int i = 0; i < LOC_SIZE; i++){
		roomLayout[i] = new char[LOC_SIZE];
	}
}

/*	
	delete method for Room, since we have to delete the arrays, yo
	Putting this in the destructor is causing errors.
	@author Andre Allan Ponce

void Location::deleteArray(){
	if(height > 0){
		if(width > 0){
			for(int i = 0; i < height; i++){
				delete [] roomLayout[i];
			}
		}
		delete [] roomLayout;
	}
}
//*/

/*// @author Andre Allan Ponce
bool Location::doesRoomHaveCloset(){
	return hasCloset;
}


// @author Andre Allan Ponce
std::string Location::draw(){
	std::string layout = "";
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			layout += roomLayout[i][j];
		}
		layout += "\n";
	}
	return layout;
}
//*/
/*
	fills array using the char**
	@author Andre Allan Ponce
	@param in - the istream to be read from, should consist of a room with multiple lines

void Location::fillArray(char** room){
	roomLayout = new char*[height];
	for(int i = 0; i < height; i++){
		roomLayout[i] = new char[width];
		for(int k = 0; k < width; k++){
			// cout << i << "  " << line[i] << "\n"; // debug
			roomLayout[i][k] = room[i][k];
		}
	}
}

/*
// @author Andre Allan Ponce
int Location::getHeight(){
	return height;
}
//*/


bool Location::get_east_door(){
	return has_east_door;
}

bool Location::get_north_door(){
	return has_north_door;
}

Node* Location::getItem(int id){
	return items->remove_node(id);
}

// @author Andre Allan Ponce
int Location::getRoomID(){
	return id;
}

bool Location::get_south_door(){
	return has_south_door;
}

// @author Andre Allan Ponce
char Location::getSpaceAt(int xCoord, int yCoord){
	return roomLayout[xCoord][yCoord];
}


bool Location::get_west_door(){
	return has_west_door;
}

/*// @author Andre Allan Ponce
int Location::getWidth(){
	return width;
}

// @author Andre Allan Ponce
bool Location::isRoomClosed(){
	return isClosed;
}



// @author Andre Allan Ponce
// @returns true if player moved, false if not (because of illegal move)
bool Location::movePlayer(int xOld, int yOld, char player, int xNew, int yNew){
	if(getSpaceAt(xNew, yNew) == EMPTY_SPACE){
		resetSpace(xOld, yOld, EMPTY_SPACE);
		setPlayer(xNew, yNew, player);
		return true;
	}
	return false;
}

// @author Andre Allan Ponce
void Location::resetSpace(int xSpace, int ySpace, char space){
	roomLayout[xSpace][ySpace] = space;
}

// @author Andre Allan Ponce
void Location::setPlayer(int xPlay, int yPlay, char player){
	roomLayout[xPlay][yPlay] = player;
}
//*/

void Location::set_east_door(bool value){
	has_east_door = value;
}

void Location::set_north_door(bool value){
	has_north_door = value;
}

// @author Andre Allan Ponce
void Location::setRoomID(int idNum){
	id = idNum;
}

void Location::set_south_door(bool value){
	has_south_door = value;
}

void Location::set_west_door(bool value){
	has_west_door = value;
}
