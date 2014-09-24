
#include "room.h"
#include "hallway.h"

// @author Andre Allan Ponce
Hallway::Hallway() : Room() {

}

// @author Andre Allan Ponce
Hallway::Hallway(int idNum, int xCoord, int yCoord, int h, int w) : 
	Room(idNum,xCoord,yCoord,h,w,false,false) { // all hallways have no closets, and 4 doors
	
}