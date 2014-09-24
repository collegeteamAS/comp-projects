
#include "room.h"
#include "garage.h"

// @author Andre Allan Ponce
Garage::Garage() : Room(){

}

// @author Andre Allan Ponce
Garage::Garage(int idNum, int xCoord, int yCoord, int h, int w) : 
	Room(idNum,xCoord,yCoord,h,w,true,true){ // garages can have closets, but one door

}