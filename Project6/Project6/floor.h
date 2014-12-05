/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Floor contains the 2D array of locations the player can visit
	2014-10-30

	2014-12-03
	+ createStairs method
	+ added pointers to the up and down stairs
	+ added variable and methods that keep track and retrieve the number of rooms on this floor
	+ added method to sync doors based on coordinates
	= rewrite createStairs method to return a Location pointer to the new stairs

	2014-12-04
	 - removed sync doors. unsynced doors allows us to display fake door messages
		detecting the correct doors is given trough canMove* methods in game
//*/
#ifndef _FLOOR_H_INCLUDED_
#define _FLOOR_H_INCLUDED_

#include <string>

//class CoordList;
class StairsTile;
class Location;

class Floor {
private:
	Location*** floor;
	// the flooor

	char** map;
	// A map of the tiles surrounding player

	int numberOfCreatedRooms; // how many rooms do we have?

	int mapHeight;
	int mapWidth;

	int stairCounter; 
	// starts at 00, increases by 01 each new room.
	// we should have at least 100 rooms before making some stairs.
	// the first floor may have a differing stair counter increment
	// since it will not have a stair room at the start.

	int scoreCounter;
	// starts at 0, increases by 1 per new room
	// this room is where you supposed to drop the keys.
	// not used in debug modes

	int mineCounter;
	// starts at 10, increases by 5 for every 10 tiles, max 50

	int mineCounterTally;

	bool scoreRoom; // true if it is here

	// id of this floor
	// the index of where this floor is at in game vector
	int id;

	// Floordinates!
	StairsTile* upStairs;
	StairsTile* downStairs;

	// how many rows and cols of tiles are shown on the map
	static const int MAP_TILES_VISIBLE = 2;

	void deleteFloor();
	void deleteMap();

	void drawMap(int x, int y, char sym); 
	/*// fills the char map array
	@param x - the x coordinate of the player
	@param y - the y coordinate of the player
	@param sym - the player's symbol
	//*/

	void drawRoom(int startX, int startY, int x, int y, char sym);
	/*// draws a single room onto map
	@param startX - the x coordinate on the map to start drawing
	@param startY - the y coordinate on the map to start drawing
	@param x - the x coordinate of the player
	@param y - the y coordinate of the player
	@param sym - the player's symbol
	//*/

	void drawRoomBlank(int startX, int startY);
	/*// draws a blank room onto map
	@param startX - the x coordinate on the map to start drawing
	@param startY - the y coordinate on the map to start drawing
	//*/

	// unused methods for drawing partial maps using linked list and
	// writeconsoleoutput
	// void drawMapPartial(int x, int y, char sym, Coord_List* list);
	//void drawRoomPartial(int startX, int startY, int x, int y, char sym, Coord_List* list);
	//void drawRoomBlankPartial(int startX, int startY, Coord_List* list);

public:
	enum Constants{
		// height and width -- each floor has max 900 rooms
		// 700 is the *important room* cutoff
		// all required rooms should spawn by this point

		FLOOR_HEIGHT = 30,
		FLOOR_WIDTH = 30,
		
		// this is the cutoff for creating stairs
		STAIRS_GENERATION_THRESHOLD = 5,
		KEY_ADD_THRESHOLD = 10
	};

	Floor(int idNum);
	~Floor();

	void createFloor();
	void createMap();

	// stairs;
	Location* createStairs(int idNum, int x, int y, bool isUp);
	/*// create the Stairs according to isUp
		This also sets the corresponding upStairs, downStairs pointer accordingly
	@param idNum - the id of this Location
	@param x - the x coordinate of these stairs
	@param y - the y coordinate of these stairs
	@param isUp - true if these stairs face up, false if down
	@returns Location pointer to these stairs
	//*/

	int getID();
	Location* getLoc(int x, int y);
	std::string getMap();

	int getMineCount(); // auto increments minecounter

	std::string getNewMap(int x, int y, char sym);
	/*// generations and returns a new map string
	@param x - the x coordinate of the player
	@param y - the y coordinate of the player
	@param sym - the player's symbol
	@return the string representation of this map
	//*/

	int getNumberOfCreatedRooms(); 

	int getScoreCounter(); // auto increments the score counter

	int getStairCount();
	/*// gets and increments the stair counter
	@returns the current Stair Counter value and post-increments it
	//*/

	StairsTile* getStairsDown();
	StairsTile* getStairsUp();

	bool hasStairsDown();
	bool hasStairsUp();
	bool isScoreRoomHere();
	bool isValidRoom(int x, int y);

	//Coord_List* getMapPartial(int x, int y, char sym);
	// unused

	void setID(int idNum); // we probably dont need this
	void setLoc(Location* loc, int x, int y); // automatically increments the number of Rooms

	void set_room_doors(int x, int y, bool value);
	/*// sets the Location's doors at x,y to value
		used only for debugging 
	@param x - the x coordinate of the room to change doors
	@param y - the y coordinate of the room to change doors
	@param value - the value to change the location's doors
	//*/

	void setScoreRoomHere(bool value);

	/*
	void syncDoors(int x, int y);
	 syncs the doors around the room given at the coordinates
	@param x - the x coordinate of the room to sync doors
	@param y - the y coordinate of the room to sync doors
	//*/
};

#endif