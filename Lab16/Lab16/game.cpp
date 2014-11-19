/*//
	Andre Allan Ponce
	Steve Suh
	-> modified version of lab16's game.cpp
//*/

#include "game.h"
#include "key.h"
#include "door.h"
#include "menutext.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

Game::Game()
{
	srand(time(0));

	world = 0;
	rows = cols = 0;
	playerRow = 0;
	playerCol = 0;
}

//THE Game VERSION OF THE setUpGame() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::setUpGame()
{
	int r, c;
	std::string locationType;

	ifstream dataFile(MenuText::FILE_NAME_LAYOUT);

	if (!dataFile)
	{
		std::cout << MenuText::ERROR_FILE_CANNOT_READ << "\n";
	}

	//Read the number of rows and columns from the file
	dataFile >> rows >> cols;

	//Now we need to dynamically allocate world to be a 2D array of pointers to Locations
	world = new Location **[rows];
	for (r = 0; r < rows; r++)
	{
		world[r] = new Location *[cols];
	}

	//Next, go and initialize all of the pointers in the array to NULL
	for (r = 0; r < rows; r++)
	{
		for (c = 0; c < cols; c++)
		{
			dataFile >> locationType;
		
			if(locationType.c_str()[0] == Key::SYMBOL_KEY){
				world[r][c] = new Key();
			}
			else if(locationType.c_str()[0] == Door::SYMBOL_DOOR){
				world[r][c] = new Door();
			}
			else //put a default Location object
			{
				world[r][c] = new Location;
			}
		}
	}
	dataFile.close();

	world[0][0]->setVisited(true);
}

//THE Game VERSION OF THE draw() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::drawGame()
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (r == playerRow && c == playerCol)
				std::cout << Player::SYMBOL_PLAYER;
			else
				world[r][c]->draw();
		}
		std::cout << "\n";
	}
}

//THE Game VERSION OF THE playGame() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::playGame()
{
	int state = 1;
	char move = ACTION_BLANK;

	instructions();
	setUpGame();  //Make sure level is set up for the first level

	drawGame();
	while (state > 0) //the game continues as long as state is not zero
	{
		//Handle player move
		do
		{
			std::cout << MenuText::MENU_ASK_DIRECTION;
			std::cin >> move;
			std::cout << "\n";
			if (move == ACTION_UP && playerRow > 0)
			{
				playerRow--;
			}
			else if (move == ACTION_DOWN && playerRow < rows-1)
			{
				playerRow++;
			}
			else if (move == ACTION_LEFT && playerCol > 0)
			{
				playerCol--;
			}
			else if (move == ACTION_RIGHT && playerCol < cols-1)
			{
				playerCol++;
			}
			else
			{
				std::cout << MenuText::ERROR_INVALID_INPUT << "\n";
				move = ACTION_BLANK;
			}
		} while (move == ACTION_BLANK);

		system("cls");
		drawGame();
		//resolve actions involved with that move
		state = world[playerRow][playerCol]->visit(p);
	}
}

void Game::instructions()
{
	cout << MenuText::MENU_HELP;
	system("pause");
	system("cls");
}

Game::~Game()
{
	int r, c;

	if (world != 0) //delete the world if it has been made to point to something
	{
		//first delete all of the objects
		for (r = 0; r < rows; r++)
		{
			for (c = 0; c < cols; c++)
			{
				delete world[r][c];
			}
		}

		//now delete all of the columns on each row
		for (r = 0; r < rows; r++)
		{
			delete [] world[r];
		}

		//finally, we can delete the array
		delete [] world;
	}
}