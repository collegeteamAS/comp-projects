
#ifndef _GAME_H_INCLUDED_
#define _GAME_H_INCLUDED_

//#include <wincon.h>
//#include <Windows.h>
#include "roomdata.h"

class Location;
class Player;
//class Room;
//struct INPUT_RECORD;

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

	bool isFinalDoorIn;

	// where is the player right now?
	int currX;
	int currY;

	// methods
	void changeRoom(int move);
	Location* createRandomRoom(int x, int y, int roomDoor);
	Location* createRoom(int id, int x, int y);
	void createWorld();
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

	int getRandomNumber();

	void printGame();
	void readInFile(std::string fileName);
	void runGame();
};

#endif