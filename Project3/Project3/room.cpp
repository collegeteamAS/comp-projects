
#include <vector>
#include "room.h"
#include "location.h"

// @author Andre Allan Ponce
Room::Room() : Location(), id(-1), roomLayout(0), x(-1), y(-1),hasCloset(false),width(-1),height(-1),leftDoorRow(-1),rightDoorRow(-1),upDoorCol(-1),downDoorCol(-1){

}

// @author Andre Allan Ponce
Room::Room(int idNum, int xCoord, int yCoord, int h, int w) : Location(), id(idNum), roomLayout(0), x(xCoord),y(yCoord),hasCloset(false),width(w),height(h),leftDoorRow(-1),rightDoorRow(-1),upDoorCol(-1),downDoorCol(-1){

}

// @author Andre Allan Ponce
bool Room::doesRoomHaveCloset(){
	return hasCloset;
}

// @author Andre Allan Ponce
std::string Room::draw(){
	// return what this room looks like
}

// @author Andre Allan Ponce
void Room::fillArray(std::string layout){
	//fill what this room looks like
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

// @author Andre Allan Ponce
void Room::setDownDoorCol(int c){
	downDoorCol = c;
}

// @author Andre Allan Ponce
void Room::setLeftDoorRow(int r){
	leftDoorRow = r;
}

// @author Andre Allan Ponce
void Room::setRightDoorRow(int r){
	rightDoorRow = r;
}

// @author Andre Allan Ponce
void Room::setUpDoorCol(int c){
	upDoorCol = c;
}