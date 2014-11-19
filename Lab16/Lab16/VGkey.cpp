/*//
	Andre Allan Ponce
//*/

#include "VGkey.h"
#include "player.h"
#include "videoGame.h"
//#include "key.h"

VGkey::VGkey(char symbol) : Key(symbol){

}

void VGkey::draw(){
	if (visited == true && taken == false)
	{
		Videogame::renderBitMap( ((int)(symbol)) );
			//This code converts the symbol (a char) to an integer
			//to be used as the texture ID for this type of object
	}
}

int VGkey::visit(Player& p){
	if(visited == false){
		Videogame::setMessage2(MenuText::GAME_KEY_FOUND);
	}
	visited = true;
	return 1;
}