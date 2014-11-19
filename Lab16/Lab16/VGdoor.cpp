/*//
	Andre Allan Ponce
//*/

#include "VGdoor.h"
#include "player.h"
#include "videoGame.h"

VGdoor::VGdoor(char symbol) : Door(symbol){

}

void VGdoor::draw(){
	if(visited == true){
		Videogame::renderBitMap( ((int)(symbol)) );
	}
}

int VGdoor::visit(Player& p){
	if(visited == false){
		Videogame::setMessage2("You found the door!");
	}
	visited = true;
	return 1;
}