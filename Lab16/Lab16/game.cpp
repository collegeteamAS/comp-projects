//FileName:		game.cpp
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the methods for the game class

#include "game.h"
#include "key.h"
#include "door.h"
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

	ifstream dataFile("maze.txt");

	if (!dataFile)
	{
		cout << "Could not open maze.txt for reading" << endl;
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
		
			if(locationType == "k"){
				world[r][c] = new Key('k');
			}
			else if(locationType == "d"){
				world[r][c] = new Door('d');
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
				cout << "P";
			else
				world[r][c]->draw();
		}
		cout << endl;
	}
}

//THE Game VERSION OF THE playGame() METHOD IS NOT USED IN THIS LAB ACTIVITY
void Game::playGame()
{
	int state = 1;
	char move = 'x';

	instructions();
	setUpGame();  //Make sure level is set up for the first level

	drawGame();
	while (state > 0) //the game continues as long as state is not zero
	{
		//Handle player move
		do
		{
			cout << "What direction do you want to move (u,d,l,r)? ";
			cin >> move;
			cout << endl;
			if (move == 'u' && playerRow > 0)
			{
				playerRow--;
			}
			else if (move == 'd' && playerRow < rows-1)
			{
				playerRow++;
			}
			else if (move == 'l' && playerCol > 0)
			{
				playerCol--;
			}
			else if (move == 'r' && playerCol < cols-1)
			{
				playerCol++;
			}
			else
			{
				cout << "You can't do that!" << endl;
				move = 'x';
			}
		} while (move == 'x');

		system("cls");
		drawGame();
		//resolve actions involved with that move
		state = world[playerRow][playerCol]->visit(p);
	}
}

void Game::instructions()
{
	std::string name;

	cout << "Welcome to the exciting game of Find the Crystals. In this game you use the" << endl;
	cout << "arrow keys to navigate around on the game board and find crystals." << endl;
	cout << "\nGood Luck!" << endl;
	
	cout << "Please enter your name: ";
	cin >> name;
	p.setName(name);
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