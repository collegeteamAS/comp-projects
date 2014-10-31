/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	
//*/
#ifndef _TILE_H_INCLUDED_
#define _TILE_H_INCLUDED_

#include "location.h"

class Item;
class Node;

class Tile : public Location{
protected:
	int floor_id; // what floor this is on
	bool hasKey; // true if we have key, false if not
	int numKeys; // 0 <= numKeys <= 3

	void addExistingKey(Item* key);
	/*// adds a key item to the room (not to be confused with creating a key item and putting it in the room)
	@param key - the key to add to this room
	//*/

public:
	enum Contsants{
		EMPTY_SPACE = ' ',

		END_GAME_CHAR = 'E',

		// coordinates of the Exit room 
		END_GAME_X = 3,
		END_GAME_Y = 1,

		TILE_HEIGHT = 5,
		TILE_WIDTH = 7,

		// Coordinates of the possible key locations
		KEY_X_0 = 1,
		KEY_Y_0 = 1,

		KEY_X_1 = 1,
		KEY_Y_1 = 5,

		KEY_X_2 = 3,
		KEY_Y_2 = 5
	};

	Tile(int idNum, int xCoord, int yCoord, int floor);

	virtual void addKey(); // for starting a tile with a key
	virtual void addItem(Node* n);
	virtual void createNewArray(char*** room);
	virtual char*** draw();

	int get_floor_id();
	virtual Node* getItem(int id);

	virtual void setFinalRoom(bool value);

};

#endif