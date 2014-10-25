#include "tile.h"

Tile::Tile(int idNum, int xCoord, int yCoord, int floor) : Location(idNum,xCoord,yCoord), 
	floor_id(floor){

}
