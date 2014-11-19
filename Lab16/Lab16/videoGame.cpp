//FileName:		Videogame.cpp
//Programmer:	Dan Cliburn
//Date:			4/22/2014
//Purpose:		This file defines the methods for the Videogame class
//See:  http://www.sdltutorials.com/sdl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-opengl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-soundbank
//for many more details on how to write an OpenGL program using SDL.
//You might also want to go to these pages which will link you to other
//tutorials on how to do stuff with SDL

#include "videogame.h"
#include "texture.h"
#include "VGcrystal.h"
#include <SDL.h>
#include <Windows.h>  //Must include this here to get it to compile
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <glut.h>  //includes gl.h and glu.h
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//Define how large the window will be
const int WINDOWWIDTH = 1200;
const int WINDOWHEIGHT = 800;

//Define ID numbers to associate with textures
const int PLAYER_TEXID = 500;  //This is NOT a value in the ASCII table
//TODO: Define constants for each of your Location subclasses
const char CRYSTAL_ID = 'C';

//Static class variables
string Videogame::message1 = "";
string Videogame::message2 = "";
string Videogame::message3 = "";

Videogame::Videogame()
{
	message1 = "";
	message2 = "";
	message3 = "";
}

void Videogame::setUpGame()
{
	int r, c;
	string locationType;

	ifstream dataFile("maze.txt");

	if (!dataFile)
	{
		cout << "Could not open maze.txt for reading" << endl;
	}

	//Read the number of rows and columns from the file
	dataFile >> rows >> cols;

	theRows = rows;
	theCols = cols;

	//Now we need to dynamically allocate world to be a 2D array of pointers to Locations
	world = new Location **[rows];
	for (r = 0; r < rows; r++)
	{
		world[r] = new Location *[cols];
	}

	//Next, go and initialize all of the pointers in the array to NULL
	//NOTE: the characters for each class are defined as constants at top of this file
	for (r = 0; r < rows; r++)
	{
		for (c = 0; c < cols; c++)
		{
			dataFile >> locationType;
		
			if (locationType == "crystal")
			{
				world[r][c] = new VGcrystal(CRYSTAL_ID);
			}
			//TODO:  check for other location subtypes here
			else //put a default Location object
			{
				world[r][c] = new Location;
			}
		}
	}
	dataFile.close();

	world[0][0]->setVisited(true);
}

//Initializes SDL and OpenGL
bool Videogame::init()
{
	display = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if ((display = SDL_SetVideoMode(WINDOWWIDTH, WINDOWHEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL )) == NULL)
	{
		return false;
	}

	glClearColor(0.3, 0.3, 0.3, 1.0);  //Will be the color of the background
	
	//Set parameters for how we want to view the scene
	glViewport(0,0, WINDOWWIDTH, WINDOWHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(WINDOWWIDTH)) / ((double)(WINDOWHEIGHT));
	glFrustum(-0.1, 0.1, -0.1/aspectRatio, 0.1/aspectRatio, 0.1, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Do OpenGL init stuff
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0); //Controls the thickness of lines

	//Now, initialize our other variables for drawing the game
	Eye[0] = Aim[0] = cols/2.0;
	Eye[2] = 1.28*rows;
	Aim[2] = rows/2.0;
	Eye[1] = rows/2.0;
	Aim[1] = 0.0;
	Up[0] = 0.0;
	Up[1] = 1.0;
	Up[2] = 0.0;

	//NOTE: the texture IDs are defined as constants at the top of this file
	Texture loader;
	loader.loadTexBMP("images//door.bmp", ((int)(CRYSTAL_ID)), addAlpha);  //Image for the crystal
	loader.loadTexBMP("images//player.bmp", PLAYER_TEXID, addAlpha);  //Image for the player
	//TODO:  Load more textures here

	return true;  //Everything got initialized
}

void Videogame::renderBitMap(int texID)
{
	// make sure the transparent part of the texture isn't drawn
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	// select the texture
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
		// bottom left corner
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(0.0, 0.0, 0.0);
					
		// bottom right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);

		// top right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
					
		// top left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//Draws the Heads Up Display (HUD) that shows players'info
void Videogame::drawHUD()
{
	unsigned int i;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(WINDOWWIDTH)) / ((double)(WINDOWHEIGHT));
	int width = 260;  //TODO:  Make this bigger if you need more space for your messages
	int height = width/aspectRatio;
	glOrtho(0, width, 0, height, -10, 10);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);  //COLOR OF THE TEXT MESSAGES
	glPushMatrix();
		glTranslatef(0.0, .95*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message1.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message1[i]);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, .90*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message2.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message2[i]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, .85*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message3.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message3[i]);
	glPopMatrix();

	//Put the program back in the proper projection for drawing the rest of the game
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1/aspectRatio, 0.1/aspectRatio, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Videogame::drawGame()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Establish the eye and aim positions, and the up vector 
	//Think holding a digital camera and pointing it at what you want to take a picture of
	gluLookAt(Eye[0],Eye[1],Eye[2], Aim[0],Aim[1],Aim[2], Up[0],Up[1],Up[2]);
 
	//Go through each location and render what the user should see
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			glColor3f(0.1, 0.4, 0.1);  //Sets the color of the ground
			if (playerRow == r && playerCol == c) //Is this the square under the player?
			{
				glColor3f(0.1, 0.8, 0.1);  //If so, then draw this square a different color
			}
			if (world[r][c]->getVisited() == true)
			{
				//Draw the dark green square that makes up the ground at this location
				glBegin(GL_QUADS);
					glVertex3f(c, 0.0, r);
					glVertex3f(c, 0.0, r+1.0);
					glVertex3f(c+1.0, 0.0, r+1.0);
					glVertex3f(c+1.0, 0.0, r);
				glEnd();
			
				//Now render what the player should see at this location
				glPushMatrix(); //Save the current transformation state
					glTranslatef(c, 0, r+0.7);
					world[r][c]->draw(); //Go render the appropriate image (if any) for this location
				glPopMatrix();
			}
		}
	}

	//Now render the Player
	glPushMatrix(); //Save the current transformation state
		glTranslatef(playerCol, 0, playerRow+0.3);
		renderBitMap(PLAYER_TEXID);
	glPopMatrix();

	//Draw the text messages.  HUD stands for Heads Up Display
	drawHUD();
	
	SDL_GL_SwapBuffers();
}

char Videogame::handleEvent(SDL_Event *theEvent) 
{ 
	switch(theEvent->type)
	{
		case SDL_QUIT:  //User clicks on the 'X' in the Window
		{
			endGame();
			exit(0);
			return 'X';
		}
		case SDL_KEYDOWN:
		{
			if (theEvent->key.keysym.sym == SDLK_LEFT || theEvent->key.keysym.sym == SDLK_a)
			{ 
			   return 'l'; 
			}
			else if (theEvent->key.keysym.sym == SDLK_RIGHT || theEvent->key.keysym.sym == SDLK_d)
			{ 
			   return 'r'; 
			} 
			else if (theEvent->key.keysym.sym == SDLK_UP || theEvent->key.keysym.sym == SDLK_w)
			{ 
			   return 'u';
			}
			else if (theEvent->key.keysym.sym == SDLK_DOWN || theEvent->key.keysym.sym == SDLK_s)
			{ 
			   return 'd';
			}
			else if (theEvent->key.keysym.sym == SDLK_e){ // pick up
				return 'e';
			}
			else if (theEvent->key.keysym.sym == SDLK_q){ // drop item
				return 'q';
			}
			else if (theEvent->key.keysym.sym == SDLK_ESCAPE){
				endGame();
				exit(0);
				return 'X';
			}
		}
	 } 
	 return 'z';
}

void Videogame::playGame()
{
	int state = 1;
	char choice = 'z';

	instructions();
	setUpGame();  //Make sure everything is set up for the first level

	if (!init())  //This function (defined above) sets up OpenGL and SDL
	{
		cout << "Not everything was initialized" << endl;
		return;
	}
	SDL_Event events;  //Makes and SDL_Events object that we can use to handle events
	SDL_PollEvent(&events); //This initializes the events object

	while (state != 10) //the game continues as long as state is not 10 (which for now is forever)
	{
		do
		{
			choice = 'z';
			message1 = "Use WASD to move, E to pick up item, Q to drop";
			drawGame();
			while (SDL_PollEvent(&events)) 
			{
				choice = handleEvent(&events);
			}

			if (choice == 'u' && playerRow > 0)  //Check to see if the player pressed 'u'
			{
				playerRow--;					//if the player pressed 'u' subtract one from his/her row
			}
			else if(choice == 'd' && playerRow < theRows-1){
				playerRow++;
			}
			else if(choice == 'r' && playerCol < theCols-1){
				playerCol++;
			}
			else if(choice == 'l' && playerCol > 0){
				playerCol--;
			}
			else if(choice == 'e'){

			}
			else if(choice == 'q'){

			}
			else if (choice != 'z')  //User made an illegal move
			{
				choice = 'z';
				message2 = "You can't do that!";
				drawGame();
				Sleep(500);
			}

		} while (choice == 'z');  //stays in this loop until the user presses a key

		//resolve actions involved with that move
		message1 = message2 = message3 = "";
		state = world[playerRow][playerCol]->visit(p);
		drawGame();
	}
	Sleep(4000); //pause for 4 seconds before ending the game
	endGame();
	system("pause");
}

void Videogame::endGame()
{
	SDL_Quit();
}