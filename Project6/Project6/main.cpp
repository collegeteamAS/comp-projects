
/*
Andre Allan Ponce
a_ponce1@u.pacific.edu
Steve Suh
h_suh@u.pacific.edu
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
