
#ifndef _TILE_H_INCLUDED_
#define _TILE_H_INCLUDED_

#include "location.h"

class Item;
class Node;

class Tile : public Location{
protected:
	// just in case
	int floor_id;
	bool hasKey; // true if we have key, false if not
	int numKeys; // 0 <= numKeys <= 3

	void addExistingKey(Item* key);
	// for adding an existing key to this room

public:
	enum Contsants{
		EMPTY_SPACE = ' ',
		TILE_HEIGHT = 5,
		TILE_WIDTH = 7,

		KEY_X_0 = 1,
		KEY_Y_0 = 1,

		KEY_X_1 = 1,
		KEY_Y_1 = 5,

		KEY_X_2 = 3,
		KEY_Y_2 = 5,

		KEY_ID = 1
	};

	Tile(int idNum, int xCoord, int yCoord, int floor);

	virtual void addKey(); // for starting a tile with a key
	virtual void addItem(Node* n);

	virtual void createNewArray(char*** room);
	virtual char*** draw();
	//virtual void fillArray(char*** room);

	int get_floor_id();
	virtual Node* getItem(int id);

};

#endif