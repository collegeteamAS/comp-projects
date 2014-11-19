/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Floor contains the 2D array of locations the player can visit
	2014-10-30
//*/
#ifndef _FLOOR_H_INCLUDED_
#define _FLOOR_H_INCLUDED_

#include <string>

class Location;
class Coord_List;

class Floor {
private:
	Location*** floor;
	// the flooor

	char** map;
	// A map of the tiles surrounding player

	int mapHeight;
	int mapWidth;

	// id of this floor
	// 0 - debug
	// 1 - basement
	// 2 - ground // currently the only one used
	// 3 - upper
	int id;

	// we need this to empty a spot
	static const char ROOM_BLANK = ' ';

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
		// height and width
		FLOOR_HEIGHT = 30,
		FLOOR_WIDTH = 30
		
	};

	Floor(int idNum);
	~Floor();

	void createFloor();
	void createMap();

	int getID();
	Location* getLoc(int x, int y);
	std::string getMap();

	int getMapSize();

	std::string getNewMap(int x, int y, char sym);
	/*// generations and returns a new map string
	@param x - the x coordinate of the player
	@param y - the y coordinate of the player
	@param sym - the player's symbol
	@return the string representation of this map
	//*/

	//Coord_List* getMapPartial(int x, int y, char sym);
	// unused

	void setID(int idNum); // we probably dont need this
	void setLoc(Location* loc, int x, int y);

	void set_room_doors(int x, int y, bool value);
	/*// sets the Location's doors at x,y to value
		used only for debugging 
	@param x - the x coordinate of the room to change doors
	@param y - the y coordinate of the room to change doors
	@param value - the value to change the location's doors
	//*/
};

#endif