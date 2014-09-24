

// #include <vector>
// #include <sstream>
// #include <iostream> // debug
#include <string>
#include "location.h"


// @author Andre Allan Ponce
Location::Location() : 
	x(-1), 
	y(-1),
	id(-1), 
	roomLayout(0),
	hasCloset(false),
	isClosed(true),
	width(-1),
	height(-1){

}

// @author Andre Allan Ponce
Location::Location(int idNum, int xCoord, int yCoord, int h, int w, bool closet, bool closed) : 
	x(xCoord), 
	y(yCoord),
	id(idNum),
	roomLayout(0),
	hasCloset(closet),
	isClosed(closed),
	width(w),
	height(h){
	
}

// @author Andre Allan Ponce
void Location::createArray(){
	roomLayout = new char*[height];
}

/*	
	delete method for Room, since we have to delete the arrays, yo
	Putting this in the destructor is causing errors.
	@author Andre Allan Ponce
*/
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

// @author Andre Allan Ponce
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

/*
	fills array using the char**
	@author Andre Allan Ponce
	@param in - the istream to be read from, should consist of a room with multiple lines
*/
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
//*/

// @author Andre Allan Ponce
int Location::getHeight(){
	return height;
}

// @author Andre Allan Ponce
int Location::getRoomID(){
	return id;
}

// @author Andre Allan Ponce
char Location::getSpaceAt(int xCoord, int yCoord){
	return roomLayout[xCoord][yCoord];
}

// @author Andre Allan Ponce
int Location::getWidth(){
	return width;
}

// @author Andre Allan Ponce
bool Location::isRoomClosed(){
	return isClosed;
}
<<<<<<< HEAD
*/
=======

// @author Andre Allan Ponce
// @returns true if player moved, false if not (because of illegal move)
bool Location::movePlayer(int xOld, int yOld, char player, int xNew, int yNew){
	if(getSpaceAt(xNew, yNew) == EMPTY_SPACE || getSpace(xNew,yNew) == ){
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

/*
// @author Andre Allan Ponce
void Location::setLocationCloset(bool value){
	hasCloset = value;
}//*/

// @author Andre Allan Ponce
void Location::setRoomID(int idNum){
	id = idNum;
}
>>>>>>> working
