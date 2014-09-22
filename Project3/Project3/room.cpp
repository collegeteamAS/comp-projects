

// #include <vector>
// #include <sstream>
// #include <iostream> // debug
#include <string>
#include "location.h"
#include "room.h"


// @author Andre Allan Ponce
Room::Room() : Location(), id(-1), roomLayout(0),x(-1), y(-1),hasCloset(false),width(-1),height(-1){

}

// @author Andre Allan Ponce
Room::Room(int idNum, int xCoord, int yCoord, int h, int w) : Location(), id(idNum),roomLayout(0),x(xCoord),y(yCoord),hasCloset(false),width(w),height(h){
	
}

// @author Andre Allan Ponce
void Room::createArray(){
	roomLayout = new char*[height];
}

/*	
	delete method for Room, since we have to delete the arrays, yo
	Putting this in the destructor is causing errors.
	@author Andre Allan Ponce
*/
void Room::deleteArray(){
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
bool Room::doesRoomHaveCloset(){
	return hasCloset;
}

// @author Andre Allan Ponce
std::string Room::draw(){
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
	fills array using an istream
	@author Andre Allan Ponce
	@param in - the istream to be read from, should consist of a room with multiple lines

void Room::fillArray(std::stringstream& in){
	roomLayout = new char*[height];
	std::string line = "";
	for(int i = 0; i < height; i++){
		std::getline(in,line);
		cout << i << " " << line << "\n";
		fillArrayRow(line,i);
		in.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // apparently getline has been overloaded by sstream, so we have to do this to enter next line.
	}
}
//*/

// @author Andre Allan Ponce
void Room::fillArrayRow(std::string line, int row){
	roomLayout[row] = new char[width];
	for(int i = 0; i < width; i++){
		// cout << i << "  " << line[i] << "\n"; // debug
		roomLayout[row][i] = line[i];
	}
}

// @author Andre Allan Ponce
int Room::getHeight(){
	return height;
}

// @author Andre Allan Ponce
int Room::getRoomID(){
	return id;
}

// @author Andre Allan Ponce
int Room::getWidth(){
	return width;
}

// @author Andre Allan Ponce
int Room::getX(){
	return x;
}

// @author Andre Allan Ponce
int Room::getY(){
	return y;
}

// @author Andre Allan Ponce
void Room::setRoomCloset(bool value){
	hasCloset = value;
}

// @author Andre Allan Ponce
void Room::setRoomID(int idNum){
	id = idNum;
}