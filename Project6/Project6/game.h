/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu

	2014-12-02
	= organized code
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
private:
	std::vector<Floor*>* world; // the world

	LocationData locations;
	// holds roomlayout data for the tiles

	Player* player; // the player
	//Player* monster; // the monster

	int playerFloor;
	// separate int that will hold player's previous floor for comparison after
	// examine has been done on a stairTile

	int numberOfFloors;
	// how many floors we got

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
	// not used in debug modes

	bool isFinalDoorIn; // here is the end
	int finalRoomX; // the endgame x coord
	int finalRoomY;  // the endgame room y coord

	std::string activeText; // debug
	std::string modeText; // what you should be doing right now.

	bool arePreviousStairsUp(int x, int y, int floor);
	/*// checks if the previous floor's stairs were up or down
	@param x - x-coordinate of the previous stairs
	@param y - y-coordinate of the previous stairs
	@param floor - the index of the previous floor
	@returns true if the stairs at (x,y) at Floor index floor were facing up, false if facing down
	//*/

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

	int distanceFromEdge(int coordinate);
	/*// calculates the distance this coordinate is from an edge 
		this uses the START_ROOM_X (the center of the map)
		coordinate to calculate this value
	@param coordinate - a spot
	@returns the distance the spot is from an edge
	//*/

	void dropOffItem();

	bool edgeChanceMaker(int distance);
	/*// decides if this is edge based on distance to edge
	@param distance - distance from this location to edge
	@returns true if this will be an edge, false if not
	//*/

	int edgeCheck(bool xEdge, bool yEdge, int x, int y);
	/*// checks which edges this location is
		LOCATION MUST BE LOCATED ON EDGE (xEdge == true || yEdge == true)
	@param xEdge - true if x is an edge, false if not
	@param yEdge - ture if y is an edge, false if not
	@param x - the x-coordinate of this room
	@param y - the y-coordinate of this room
	@returns id of acceptable room
	//*/

	void examine();
	/*// activated when the player hits e key
		this should call the examine method of the current room
	//*/

	void examineResults();
	/*// checks status of player and adjusts game if necessary
		cases:
			moving player to different floor
			(thats all for now)
	//*/

	void gameStates(int& old_state, bool& mapPrint, clock_t& startTime);
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

	Floor* makeFloor(int id); // id is the index of this floor
	Location* makeRoom(int id, int x, int y, int flor);
	bool movePlayer(int xMove, int yMove); // moves player on x and y grid
	void movePlayerFloor();
	void pickUpItem();
	void preGameInit();

	void setupDoors(Location* loc, int id);
	/*// sets the door bools based on the id
	@param loc - pointer to location to adjust doors
	@param id - id of the room
	//*/

	bool isThisAnEdgeNow(int chance);
	/*// simply decides to make edge using the givenchance
	@param chance - the chance (out of 100) of this being an edge
	@returns true if this becomes edge, false if not
	//*/

	int tileIDRandomizer(int x, int y);
	/*// picks a tiletype based on location (x,y)
		This utilizes a percentage chance of certain tiles spawning,
		dependent on the distance of this location from the edge
	@param x - the x-coordinate of this location
	@param y - the y-coordinate of this location
	@returns an ID number for a tiletype
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
		START_FLOOR = 0, // this should be the ground floor
		START_ROOM_X = 15,
		START_ROOM_Y = 15,

		// The player is always in the middle of the map 
		CENTER_PLAYER_X = 22,
		CETNER_PLAYER_Y = 22,

		// how many floors do we have
		// change this
		WORLD_SIZE = 1,

		// the chances for certian tiles to spawn
		CHANCE_EDGE_ROW_ONE = 50,
		CHANCE_EDGE_ROW_TWO = 42,
		CHANCE_EDGE_ROW_THREE = 38
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
	//void printGamePartial();
	void printHelp();
	void readInFile(std::string fileName);
	// @author Andre Allan Ponce
	// reads in room file format:
	/*
		# <-- id 
		+-- --+
		|     |
		       
		|     |
		+-- --+
		(Tile DESIGN)
	*/

	void runGame();
};

#endif
