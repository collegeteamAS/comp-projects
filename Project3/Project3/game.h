/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu
*/

#ifndef _GAME_H_INCLUDED_
#define _GAME_H_INCLUDED_

#include "roomdata.h"
<<<<<<< HEAD
#include "item.h"
=======
#include "itemdata.h"

>>>>>>> e692805bc743cdf709b3569e29a559e39528d45b
class Location;
class Player;
class Item;

class Game {
private:
	Location*** world; // the world
	RoomData roomData; 
	ItemData itemData;  

	Player* player; // the player
	Player* monster; // the monster
	
	/* STATE machine:
		0 - start up state, reading in data, preparing game
		1 - game start, first mode:
			player active
			monster inactive
		2 -	second mode: ---------------------------- we only got up to here, though, not enough time, sorry --------------- (monsters are invisible)
			player active
			monster active, random movement
		3 - third mode:
			player active
			monster active, moves toward player slowly, player can hide from monster by going in closets
		4 -	fourth mode:
			player active
			monster active, moves normal speed to player, player cannot hide.
		5 -	finish game:
			tell player they have lost/won
			either: delete arrays, shutdown game
			OR: ask player to play again.
	*/
	int state;

	bool isFinalDoorIn; // there was supposed to be an end, eventually

	std::string activeText; // debug

	// where is the player right now?
	int currX;
	int currY;

	// methods
	void changeRoom(int move);
	Location* createRandomRoom(int x, int y, int roomDoor); // rooms are randomy generated
	Location* createRoom(int id, int x, int y);
	void createWorld();
	int detectItemID();
	int findItemID(char sym);
	void getKeyInput(unsigned short key, Location* currRoom);
	int isLocAtEdge(int x, int y, Location* currRoom);
	Location* makeRoom(int id, int x, int y);
	void moveMonster();
	void movePlayer(int move, Location* currRoom);
	void placePlayerInNewRoom(int move, Player* play, char sym);
	void preGameInit();

public:
	enum Constants{
		PLAYER_SYMBOL = 'O',
		MONSTER_SYMBOL = 'X',
		CLOSET_SYMBOL = 'C',
		
		
		JUNK_SYMBOL = 'j',
		VASE_SYMBOL = 'v',
		TABLE_SYMBOL = 'T',
		CHAIR_SYMBOL = 'c',
		LAMP_SYMBOL = 'l',
		BED_SYMBOL = 'B',
		CANDLE_SYMBOL = 'I',
		DISH_SYMBOL = 'd',
		DUST_SYMBOL = 'w',
		FORK_SYMBOL = 'f',
		TOILET_SYMBOL = 'e',
		BATHTUB_SYMBOL = 'u',
		MIRROR_SYMBOL = 'H',
		BLOOD_SYMBOL = '*',
		CD_SYMBOL = 'a',
<<<<<<< HEAD
		*/
=======
		//*/
>>>>>>> e692805bc743cdf709b3569e29a559e39528d45b
		EXIT_SYMBOL = 'E',
		WALL_SYMBOL_A = '|',
		WALL_SYMBOL_B = '-',
		WALL_SYMBOL_C = '=',
		CORNER_SYMBOL = '+',

		// size of world ( num x num)
		WORLD_SIZE = 30,

		// STATE MACHINE
		STATE_WAIT = -1,
		STATE_PRE_GAME = 0,
		STATE_LEVEL_ONE = 1,
		STATE_LEVEL_TWO = 2,
		STATE_LEVEL_THREE = 3,
		STATE_LEVEL_FOUR = 4,
		STATE_GAME_FINISH = 5,

		// MOVE IDS
		// we might not need this anymore
		MOVE_NONE = 0,
		MOVE_LEFT = 1,
		MOVE_UP = 2,
		MOVE_RIGHT = 3,
		MOVE_DOWN = 4,

		// STARTING ROOMS
		START_ROOM_X = 15, // this actually is both x,y for the first bedroom (starting room)
		START_ROOM_Y = 14, // this is only used for the first (starting) hallway y coordinate

		// START COORDinates (for player)
		START_PLAYER_X = 3,
		START_PLAYER_Y = 5
	};

	Game();
<<<<<<< HEAD
	void displayInventory();
=======
>>>>>>> e692805bc743cdf709b3569e29a559e39528d45b

	int getRandomNumber();

	void printGame();
	void readInFile(std::string fileName);
	void readInItemFile(std::string fileName);
	void runGame();

	Item* retrieveItem(int id);


	int orbProb [8]; // prob = 1/n
	void updateOrbProbability(); //updating the probability of getting rarer orbs little bit easier(0.1%>5% for instance) if you have more common orbs
	bool orbInventory [8]; //array of storing bool of whether you got that orb
	void displayInventory(); // displaying the orbs you have
	std::string orbInventoryNames [8]; //green, yellow, red, white, black, light, dark, pale

};

#endif
