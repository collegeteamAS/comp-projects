
#ifndef _GAME_H_INCLUDED_
#define _GAME_H_INCLUDED_

#include "roomdata.h"

class Location;
class Player;
class Room;

class Game {
private:
	Location*** world;
	RoomData roomData;

	Player* player; // the player
	Player* monster; // the monster
	
	/* STATE machine:
		0 - start up state, reading in data, preparing game
		1 - game start, first mode:
			player active
			monster inactive
		2 -	second mode:
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

	// where is the player right now?
	int currX;
	int currY;

	// methods
	Room* createRoom(int id, int x, int y);
	void createWorld();
	void getKeyInput(INPUT_RECORD* irIn, Room* currRoom);
	void moveMonster();
	void movePlayer();
	void preGameInit();

public:
	enum Constants{
		PLAYER_SYMBOL = 'O',
		MONSTER_SYMBOL = 'X',
		CLOSET_SYMBOL = 'C',
		
		/*JUNK_SYMBOL = 'j',
		VASE_SYMBOL = 'v',
		TABLE_SYMBOL = 't',
		CHAIR_SYMBOL = 'c',
		LAMP_SYMBOL = 'l',
		BED_SYMBOL = 'b',
		CANDLE_SYMBOL = 'I',
		DISH_SYMBOL = 'd',
		DUST_SYMBOL = 'w',
		FORK_SYMBOL = 'f',
		TOILET_SYMBOL = 'e',
		BATHTUB_SYMBOL = 'u',
		MIRROR_SYMBOL = '-',
		BLOOD_SYMBOL = '*',
		CD_SYMBOL = 'a',
		*/
		// size of world ( num x num)
		WORLD_SIZE = 30,

		// STATE MACHINE
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
		START_PLAYER_Y = 7
	};

	Game();

	void printGame();
	void readInFile(std::string fileName);
	void runGame();
	int detectItemID();
	Item* retrieveItem();
};

#endif