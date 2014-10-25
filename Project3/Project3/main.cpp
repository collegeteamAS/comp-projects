
/*
Andre Allan Ponce
a_ponce1@u.pacific.edu
Steve Suh
h_suh@u.pacific.edu
*/


#include <string>
#include <vector>
#include <locale>
#include <fstream>
#include <iostream>
<<<<<<< HEAD
//#include <Windows.h> // keyboard input!
//#include <wincon.h> // more keyboard input
//#include <time.h>
//#include <sstream>
//#include "location.h"
//#include "room.h" // debug
=======
#include <time.h>
>>>>>>> e692805bc743cdf709b3569e29a559e39528d45b
#include "game.h"


int main(){

	// now with roomdata and game
	Game game = Game();
	game.readInFile("rooms");
	game.readInItemFile("items");
	game.runGame();

	
	//*/
	return 0;
}
