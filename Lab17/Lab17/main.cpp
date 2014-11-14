//FileName:		main.cpp
//Programmer:	Dan Cliburn
//Date:			4/15/2013
//Purpose:		This file defines the main function for a simple first person perspective video game 

#include "videogame.h"

int main(int argc, char *argv[])  //main must take these parameters when using SDL
{
	Videogame g;

	g.playGame();

	return 0;
}