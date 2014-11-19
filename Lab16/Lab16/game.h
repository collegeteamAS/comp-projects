/*//
	Andre Allan Ponce
	Steve Suh
	-> modified version of lab16 game.h
//*/

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "location.h"

class Game
{
	protected:
		Location ***world;
		Player p;

		int rows;
		int cols;
		int playerRow;
		int playerCol;

	public:
		enum Constants{

			// movement chars
			ACTION_BLANK = 'x',
			ACTION_UP = 'u',
			ACTION_LEFT = 'l',
			ACTION_RIGHT = 'r',
			ACTION_DOWN = 'd'
		};

		Game();

		//Required Methods
		void instructions();
		void setUpGame();
		void playGame();
		void drawGame();

		~Game();
};

#endif