/*//
	Steve Suh
	h_suh@u.pacific.edu

	2014-12-01
	+ creation of the exit tile

	2014-12-04
	= we still cal this exit tile, but it actually just does the score shit
//*/
#ifndef _TILE_EXIT_H_INCLUDED_
#define _TILE_EXIT_H_INCLUDED_

#include "tile.h"

class ExitTile : public Tile{
private:
	bool locked; // locked rooms cannot be unlocked

public:
	enum Constants{
		END_GAME_CHAR_UNLOCK = 'U',
		END_GAME_CHAR_LOCK = 'L',
		END_GAME_X = 3,
		END_GAME_Y = 1,

		SCORE = 100
	};
	ExitTile(int idNum, int xCoord, int yCoord, int floor, char sym = END_GAME_CHAR_UNLOCK);

	virtual void action(Player* p);
	virtual void createNewArray(char*** room);
	virtual void examine(Player* p);

};

#endif