//FileName:		game.cpp
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the methods for the Game class

#include "game.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;

Game::Game()
{
	srand((unsigned) time(0));

	world = 0;
	rows = cols = 0;
	playerRow = 0;
	playerCol = 0;
}

//THE GAME VERSION OF THE draw() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::setUpGame()
{
	;
}

//THE GAME VERSION OF THE draw() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::drawGame()
{
	;
}

//THE GAME VERSION OF THE playGame() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::playGame()
{
	;
}

//THE GAME VERSION OF THE instructions() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::instructions()
{
	;
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