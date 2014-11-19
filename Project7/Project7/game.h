/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu
*/

#ifndef _GAME_H_INCLUDED_
#define _GAME_H_INCLUDED_

#include "locationdata.h"
#include "coordlist.h"

class Location;
class Floor;
class Player;
class Item;
class LinkedList;

class Game {
protected:
	Floor** world; // the world

	LocationData locations;
	// holds roomlayout data for the tiles

	Player* player; // the player
	//Player* monster; // the monster

	/* STATE machine:
		-1- nothing
		0 - start up state, reading in data, preparing game
		1 - game start, explore
		2 - the final door has been found
		5 - game finish
		6 - game quit
	*/
	int state;

	int endGameCounter;
	// starts at 0, increases by 1 per new room
	// this room is where you supposed to drop the keys.

	bool isFinalDoorIn; // here is the end
	int finalRoomX; // the endgame x coord
	int finalRoomY;  // the endgame room y coord

	std::string activeText; // debug
	std::string modeText; // what you should be doing right now.

	// where is the player right now?
	//int currX;
	//int currY;

	// what floor is the player on right now?
	//int curr_floor;

	Location* createRandomRoom(int x, int y, int flor);
	/*// creates a random room (which really isnt random since we only have one type of tile
	@param x - the x coordinate of the room to create
	@param y - the y coordinate of the room to create
	@param flor - the floor of the room to create
	@return a pointer to the new location
	//*/

	void createWorld();
	void deletePlayer();
	void deleteWorld();
	void dropOffItem();

	void Game::gameStates(int& old_state, bool& mapPrint, clock_t& startTime);
	/*// handles other game states other than finish and pregame
	@param old_state - the old_state, used for debugging
	@param mapPrint - true if we want a new map, false if not
	@param startTime - clocking the time we started, used for debugging
	//*/

	bool getKeyInput(unsigned short key);
	/*// decides what we do based on input key
	@param key - the key we pressed
	refer to http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx for key codes
	@return true for updating the map, false if not
	//*/

	Floor* makeFloor(int id);
	Location* makeRoom(int id, int x, int y, int flor);
	bool movePlayer(int xMove, int yMove);
	void pickUpItem();
	void preGameInit();

	void setupDoors(Location* loc, int id);
	/*// sets the door bools based on the id
	@param loc - pointer to location to adjust doors
	@param id - id of the room
	//*/

	// int selectItem(); 
	// allow user to select which item to drop
	// cannot be used with the current display inventory

public:
	enum Constants{
		PLAYER_SYMBOL = 'O',

		// STATE MACHINE
		STATE_WAIT = -1,
		STATE_PRE_GAME = 0,
		STATE_EXPLORE = 1,
		STATE_FINAL_DOOR = 2,
		STATE_GAME_FINISH = 5,
		STATE_GAME_FINSH_BAD = 6,

		// STARTING FlOOR and ROOM
		START_FLOOR = 1, // this should be the ground floor
		START_ROOM_X = 15,
		START_ROOM_Y = 15,

		// The player is always in the middle of the map 
		CENTER_PLAYER_X = 22,
		CETNER_PLAYER_Y = 22,

		// how many floors do we have
		WORLD_SIZE = 1
	};

	Game();
	~Game();

	int getRandomNumber(int start, int end);
	/*// gets a random number from start to end
	@param start - the starting number of the range (inclusive)
	@param end - the ending number of the range (exclusive)
	@return an int between start (inclusive) and end (exclusive)
	//*/

	void printGame();
	void printGamePartial();
	void printHelp();
	void readInFile(std::string fileName);
	void runGame();
};

#endif
