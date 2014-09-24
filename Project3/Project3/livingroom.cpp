
#include "room.h"
#include "livingroom.h"

// @author Andre Allan Ponce
LivingRoom::LivingRoom() : OpenRoom(){

}

// @author Andre Allan Ponce
LivingRoom::LivingRoom(int idNum, int xCoord, int yCoord, int h, int w) : 
	OpenRoom(idNum,xCoord,yCoord,h,w){ // no closets in living rooms, lots of doors

}
