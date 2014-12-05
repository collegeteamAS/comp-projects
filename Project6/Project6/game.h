/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu

	2014-12-02
	= organized code

	2014-12-03
	+ added helper methods for moving the player a floor
	+ added even more methods for creating room more efficiently
	= revamped room creation
	= adjusted state machine for efficieny and better room creation

	2014-12-04
	+ added methods for saving and reading in save files
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

	bool canMoveFrom(int x, int y);
	/*// checks if the player can move from these coordinates
	@param x - the x coordinate to move from
	@param y - the y coordinate to move from
	@returns true if the player can move from here, false if not
	//*/

	bool canMoveTo(int x, int y);
	/*// checks if the player can move to these coordinates
		PRE-CONDITION: floor[x][y] != 0;
	@param x - the x coordinate to move to
	@param y - the y coordinate to move to
	@returns true if the player to here, false if not
	//*/

	void connectStairs(int previousFloor, int nextFloor, bool goingUp);
	/*// connects two stairs 
	@param previousFloor - the index of the floor we were on
	@param nextFloor - the index of the floor we are going to
	@param goingUp - true if we are going upStairs, false if down
	//*/

	/*//
		##==============================================================##
		## TILE CREATION:												##
		## When the player moves a direction, only a certain number of	##
		## tiles are valid tiles for the next room, since some tiles	##
		## have blocked doors. Thus, randomization is actually 3 less	##
		## than the total number of tiles.								##
		## If generateRandomNumber returns a tile that is invalid,		##
		## the tile is automatically forced into a basic, open tile		##
		## ( all doors are open )										##
		##==============================================================##
	//*/
	void createRandomRoom(int x, int y, int flor);
	/*// creates a random room, also decides if this is stairs or not
	@param x - the x coordinate of the room to create
	@param y - the y coordinate of the room to create
	@param flor - the floor of the room to create
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

	void examine(int& old_state);
	/*// activated when the player hits e key
		this should call the examine method of the current room
	//*/

	void examineResults(int& old_state);
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

	bool getKeyInput(unsigned short key, int& old_state);
	/*// decides what we do based on input key
	@param key - the key we pressed
	@param old_state - the previous state of the program (copy of current state unless change occurs)
	refer to http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx for key codes
	@return true for updating the map, false if not
	//*/

	bool hasValidDoor(int nextID);
	/*// checks if this tile is valid based on the current move state
		This is only for NEW ROOMS. Regular room-room movement relies on the door setups
	@param nextID - the id of the next room
	@returns true if the next room fits the door setup witht he previus tile, false if not
	//*/

	bool isThisAnEdgeNow(int chance);
	/*// simply decides to make edge using the givenchance
	@param chance - the chance (out of 100) of this being an edge
	@returns true if this becomes edge, false if not
	//*/

	Floor* makeFloor(int id); // id is the index of this floor
	Location* makeRoom(int id, int x, int y, int flor);
	Location* makeRoomScore(int id, int x, int y, int flor);
	void makeStairs(Floor* floor, int id, int x, int y, bool isUp);
	bool movePlayer(int xMove, int yMove); // moves player on x and y grid
	void movePlayerFloor();
	void movePlayerFloorNumber(bool up); // if we go up, up is true
	void pickUpItem();
	void preGameInit();
	void prepareMovePlayer();

	void setupDoors(Location* loc, int id);
	/*// sets the door bools based on the id
	@param loc - pointer to location to adjust doors
	@param id - id of the room
	//*/

	void setupRoom(Location* loc, int id);
	/*// fills a room's layout based on id, also sets the doors up, also syncs the doors accordingly
	@param loc - pointer to room
	@param id - the id of this room
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

		// STATE MACHINE
		STATE_WAIT = -1,
		STATE_PRE_GAME = 0,
		STATE_EXPLORE = 1,
		STATE_FINAL_DOOR = 2,
		STATE_GAME_FINISH = 5,
		STATE_GAME_FINSH_BAD = 6,
		STATE_MOVE_UP = 7,
		STATE_MOVE_RIGHT = 8,
		STATE_MOVE_DOWN = 9,
		STATE_MOVE_LEFT = 10,
		STATE_MOVE_FLOOR = 11,

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

	std::vector<Player*>* readInSaveFile(std::string fileName);
	void runGame();

	void savePlayersFile(std::vector<Player*>* players, std::string fileName);
	void setPlayer(Player& p);
};

#endif
