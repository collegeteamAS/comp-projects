
/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu

	2014-12:
	NEW THINGS:
	@author Andre Allan Ponce
	+ Multiple Floors - The player can navigate multiple floors by finding 'Stair' rooms
	and examining them. There are only two stairs per floor, one going up and the other
	going down. The chances for stairs appearing increase the more floors the player
	explores.
		Changed files:
		@tile_stairs.h
		@tile_stairs.cpp
		@floor.h
		@floor.cpp
		@game.h
		@game.cpp
		@player.h
		@player.cpp

	@author Andre Allan Ponce
	+ Randomly generated rooms - Each time the player enters a new room, the layout may be
	different, dependent on location and as well as the door setup in the previous room. 
	Certain rooms may have false doors as a result.
		Changed files:
		@location.h
		@location.cpp
		--and subclasses
		@game.h (More detailed explanation about tile randomization is here)
		@game.cpp

	@author Steve Suh
	+ Points System - By dropping three keys into an unlocked room and examining them, 
	the player can score points. There is only one unlocked room per floor, and all keys
	used to lock a room are deleted. Keys have a 10% chance spawning in a room, while
	unlocked rooms have a higher chance of spawning the more rooms the user creates
	in the floor.
		Changed files:
		@tile_exit.h
		@tile_exit.cpp
		@player.h
		@player.cpp
		@game.h
		@game.cpp

	@author Steve Suh
	+ Saving & loading system - a player's score is automatically saved when the game 
	exits. At start, the player can load an exisitng player or create their own. 
	Only the player's score and name is saved. The layout of the floors will be 
	completely different and unexplored next load.
		Changed files:
		@player.h
		@player.cpp
		@game.h
		@game.cpp
		@main.cpp

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
				@main.cpp
				This STL stores a list of players, loaded from file.


*/


#include <string.h>
#include <vector>
#include <locale>
#include <fstream>
#include <iostream>
#include <time.h>
#include "game.h"
#include "player.h"
#include "menutext.h"

Player* createPlayer();
void deletePlayers(std::vector<Player*>* players);
int pickPlayer(std::vector<Player*>* players);
void runGame(Game& g, std::vector<Player*>* players);

int main(){
	
	srand(time(0)); // fallback in case random_device no work
	Game game = Game();
	std::vector<Player*>* players;
	std::cout << MenuText::MESSAGE_LOADING_SAVE;
	try{
		game.readInFile(MenuText::FILENAME_TILES);
		players = game.readInSaveFile(MenuText::FILENAME_PLAYERS);
		std::cout << MenuText::MESSAGE_LOAD_SUCCESSFUL;
		runGame(game,players);
	}
	catch(std::string message){
		std::cout << message;
	}
	//*/
	return 0;
}

Player* createPlayer(){
	std::cout << MenuText::MENU_CHOOSE_PLAYER_NAME;
	std::string name;
	std::cin >> name;
	Player* play = new Player();
	play->setName(name);
	return play;
}

void deletePlayers(std::vector<Player*>* players){
	int end = players->size();
	for(int i = 0; i < end; i++){
		delete players->at(i);
	}
	delete players;
}

int pickPlayer(std::vector<Player*>* players){
	system("CLS");
	std::cout << MenuText::MENU_PLAYER_PICK << "\n" << MenuText::MENU_PLAYER_PICK_BAR << "\n" <<  MenuText::MENU_CREATE_NEW_PLAYER << "\n";
	int end = players->size();
	for(int i = 0; i < end; i++){
		std::cout << i+1 << ") ";
		std::cout << (*(*players)[i]);
		std::cout << "\n";
	}
	std::cout << MenuText::MENU_PLAYER_PICK_CHOICE_PREFIX;
	if(end == 0){
		std::cout << MenuText::MENU_PLAYER_PICK_CHOICE_SUFFIX;
	}
	else{
		std::cout << MenuText::MENU_PLAYER_PICK_CHOICE_MID << end << MenuText::MENU_PLAYER_PICK_CHOICE_SUFFIX;
	}
	int choice;
	std::cin >> choice;
	if(choice == 0){
		players->push_back(createPlayer());
		choice = players->size();
	}
	return choice-1;
}

void runGame(Game& g, std::vector<Player*>* players){
	bool invalid;
	do{
		unsigned int chosenPlayer = pickPlayer(players);
		if(chosenPlayer >= 0 && chosenPlayer < players->size()){
			invalid = false;
			g.setPlayer((*(*players)[chosenPlayer]));
		}
		else{
			invalid = true;
			system("CLS");
			std::cout << MenuText::INVALID_MENU_CHOICE << "\n";
			system("pause");
		}

	}while(invalid);
	g.runGame();
	g.savePlayersFile(players,MenuText::FILENAME_PLAYERS);
	deletePlayers(players);
}
