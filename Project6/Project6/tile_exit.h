/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu

	2014-12-01
	-creation of the exit tile
//*/
#ifndef _TILE_EXIT_H_INCLUDED_
#define _TILE_EXIT_H_INCLUDED_

#include "tile.h"

class ExitTile : public Tile{

public:
	enum Constants{
		END_GAME_CHAR = 'E',
		END_GAME_X = 3,
		END_GAME_Y = 1,
	};
	ExitTile(int idNum, int xCoord, int yCoord, char sym = END_GAME_CHAR);

	virtual void action(Player* p);
	virtual void createNewArray(char*** room);
	virtual void examine(Player* p);

};

#endif