//FileName:		videoGame.h
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the header for the Videogame class
//We will use OpenGL (www.opengl.org) and SDL (www.libsdl.org) for the game
#include <SDL.h>
#include "billboard.h"
#include "texture.h"
#include "game.h"

#ifndef VIDEOGAME_H
#define VIDEOGAME_H

class Videogame : public Game
{
	private:
		//SDL and other Graphics variables
		SDL_Surface *display;

		//Variables to handle player movement
		double Eye[3], Aim[3], Up[3];
		double MOVEANGLE;
		int xIN, yIN;

		int state;  //stores the state of the game

		//Variables to manage the Heads Up Display (HUD) display
		static string message1;
		static string message2;
		static string message3;

	public:
		Videogame();
		
		static void setMessage1(string s) {message1 = s;}
		static void setMessage2(string s) {message2 = s;}
		static void setMessage3(string s) {message3 = s;}
		static string getMessage1() {return message1;}
		static string getMessage2() {return message2;}
		static string getMessage3() {return message3;}

		bool init();  //sets up both SDL and OpenGL
		
		//These methods are redefined in the Videogame class
		void setUpGame();
		void playGame();
		void drawGame();
		void instructions();

		//These methods handle the rendering and event handling
		void handleEvent(SDL_Event *theEvent); //NOTE that the return type is different than in previous lab
		void updateGame();
		void drawHUD();
		void drawBackground();
		void endGame();
};

#endif