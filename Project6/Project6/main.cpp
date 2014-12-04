
/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu

	2014-12:
	NEW THINGS:
	+ Multiple Floors - The player can navigate multiple floors by finding 'Stair' rooms
	and examining them. 
		Changed files:
		@tile_stairs.h
		@tile_stairs.cpp
		@floor.h
		@floor.cpp
		@game.h
		@game.cpp
		@player.h
		@player.cpp

	+ Randomly generated rooms - Each time the player enters a new room, the layout may be
	different, dependent on location and as well as the door setup in the previous room. 
	Certain rooms may have false doors as a result.
		Changed files:
		@location.h
		@location.cpp
		--and subclasses
		@game.h (More detailed explanation about tile randomization is here)
		@game.cpp

	+ ONE MORE

	= STL Usage - We have been using <unordered_map> since Project3.
		For this project, I also added <vector> to contain the multiple floors.
			<unordered_map> is used in:
				@locationdata.h
				@locationdata.cpp
				This STL stores the 2D char arrays of each possible room layout, 
				which is read in from file
			<vector> is used in:
				@game.h
				@game.cpp
				This STL stores the world, which consists of multiple floors that
				can grow almost limitlessly


*/


#include <string.h>
#include <vector>
#include <locale>
#include <fstream>
#include <iostream>
#include <time.h>
#include "game.h"

int main(){
	
	srand(time(0)); // fallback in case random_device no work
	Game game = Game();
	game.readInFile("tiles");
	game.runGame();

	
	//*/
	return 0;
}
