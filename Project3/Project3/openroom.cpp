
/*
Andre Allan Ponce
a_ponce1@u.pacific.edu
*/

#include "openroom.h"

OpenRoom::OpenRoom() : Location(){

}

OpenRoom::OpenRoom(int idNum, int xCoord, int yCoord, int h, int w) : 
	Location(idNum,xCoord,yCoord,h,w,false,false){

}