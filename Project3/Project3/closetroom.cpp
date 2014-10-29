/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
*/
#include "closetroom.h"

ClosetRoom::ClosetRoom() : Location(){

}

ClosetRoom::ClosetRoom(int idNum, int xCoord, int yCoord, int h, int w) : 
	Location(idNum,xCoord,yCoord,h,w,true,true){

}