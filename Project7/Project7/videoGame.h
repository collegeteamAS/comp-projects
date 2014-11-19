//FileName:		videoGame.h
//Programmer:	Dan Cliburn
//Date:			4/22/2014
//Purpose:		This file defines the header for the Videogame class
//We will use OpenGL (www.opengl.org) and SDL (www.libsdl.org) for the game


#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "game.h"
#include <SDL.h>

class Videogame : public Game
{
	private:
		//SDL and other Graphics variables
		SDL_Surface *display;

		//Variables to handle player movement
		double Eye[3], Aim[3], Up[3];

		//Variables to manage the Heads Up Display (HUD) display
		static std::string message1;
		static std::string message2;
		static std::string message3;

		// probably uneeded
		int theRows;
		int theCols;

		void drawGameMap(int x, int y, int floor);
		void drawRoom(int x, int y, int floor);

		bool isValidRoom(int x, int y, int floor);

	public:
		Videogame();

		static void setMessage1(std::string s) {message1 = s;}
		static void setMessage2(std::string s) {message2 = s;}
		static void setMessage3(std::string s) {message3 = s;}
		static std::string getMessage1() {return message1;}
		static std::string getMessage2() {return message2;}
		static std::string getMessage3() {return message3;}

		bool init();  //sets up both SDL and OpenGL
		
		void setUpGame();
		void playGame();
		void drawGame();

		static void renderBitMap(int texID);
		char handleEvent(SDL_Event *theEvent);
		void drawHUD();
		void endGame();
};

#endif