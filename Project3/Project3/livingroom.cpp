
#include "room.h"
#include "livingroom.h"

// @author Andre Allan Ponce
LivingRoom::LivingRoom() : Room(){

}

// @author Andre Allan Ponce
LivingRoom::LivingRoom(int idNum, int xCoord, int yCoord, int h, int w) : 
	Room(idNum,xCoord,yCoord,h,w,false,false){ // no closets in living rooms, lots of doors

}
