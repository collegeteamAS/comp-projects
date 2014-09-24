
#include "room.h"
#include "bathroom.h"

// @author Andre Allan Ponce
Bathroom::Bathroom() : Room(){

}

// @author Andre Allan Ponce
Bathroom::Bathroom(int idNum, int xCoord, int yCoord, int h, int w) : 
	Room(idNum,xCoord,yCoord,h,w,false,true){ // bathrooms have showers (doesnt actually save you, though); traditional bathrooms are one way in

}