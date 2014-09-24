
#include "room.h"
#include "attic.h"

// @author Andre Allan Ponce
Attic::Attic() : Room(){

}

// @author Andre Allan Ponce
Attic::Attic(int idNum, int xCoord, int yCoord, int h, int w) : 
	Room(idNum,xCoord,yCoord,h,w,false,true){ // attics dont have closets, and usually only one way in/out

}