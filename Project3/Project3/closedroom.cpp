/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
*/
#include "closedroom.h"

ClosedRoom::ClosedRoom() : Location(){

}

ClosedRoom::ClosedRoom(int idNum, int xCoord, int yCoord, int h, int w) : 
	Location(idNum,xCoord,yCoord,h,w,false,true){

}