
#ifndef _FLOOR_H_INCLUDED_
#define _FLOOR_H_INCLUDED_

#include <string>

class Location;
class Coord_List;

class Floor {
private:
	Location*** floor;

	char** map;
	int mapHeight;
	int mapWidth;

	// id of this floor
	// 0 - debug
	// 1 - basement
	// 2 - ground
	// 3 - upper
	int id;

	// room generation chars:
	// we probably wont need all of these
	static const char ROOM_CORNER = '+';
	static const char ROOM_TOP = '-';
	static const char ROOM_SIDE = '|';
	static const char ROOM_EDGE = '=';
	static const char ROOM_BLANK = ' ';

	// how many rows and cols of tiles are shown on the map
	static const int MAP_TILES_VISIBLE = 2;

	// x and y is the center of the map, sym is the symbol of player (or whatever 
	// tahts in the center
	void drawMap(int x, int y, char sym); 
	void drawMapPartial(int x, int y, char sym, Coord_List* list);
	void drawRoom(int startX, int startY, int x, int y, char sym);
	void drawRoomBlank(int startX, int startY);
	void drawRoomPartial(int startX, int startY, int x, int y, char sym, Coord_List* list);
	void drawRoomBlankPartial(int startX, int startY, Coord_List* list);

public:
	enum Constants{
		// height and width
		FLOOR_HEIGHT = 30,
		FLOOR_WIDTH = 30
		
	};

	Floor(int idNum);

	void createFloor();
	void createMap();

	int getID();
	Location* getLoc(int x, int y);
	std::string getMap();
	Coord_List* getMapPartial(int x, int y, char sym);
	std::string getNewMap(int x, int y, char sym);


	void setID(int idNum); // we probably dont need this
	void setLoc(Location* loc, int x, int y);
	void set_room_doors(int x, int y, bool value);
};

#endif