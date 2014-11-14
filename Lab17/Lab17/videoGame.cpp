//FileName:		Videogame.cpp
//Programmer:	Dan Cliburn
//Date:			4/30/2014
//Purpose:		This file defines the methods for the Videogame class
//See:  http://www.sdltutorials.com/sdl-tutorial-basics/
//and	http://www.sdltutorials.com/sdl-opengl-tutorial-basics/
//for many more details on how to write an OpenGL program using SDL.
//You might also want to go to these pages which will link you to other
//tutorials on how to do stuff with SDL

#include <SDL.h>
#include <Windows.h>  //Must include this here to get it to compile
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <glut.h>  //include gl.h and glu.h
#include "videogame.h"
#include "VGenemy.h"
#include "VGcrystal.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//Define how large the window will be
const int WINDOWWIDTH = 1200;
const int WINDOWHEIGHT = 800;

//Define ID numbers to associate with textures
const int PLAYER_TEXID = 500;  //This is NOT a value in the ASCII table
const int TREE_TEXID = 501;  //This is NOT a value in the ASCII table
const int TREES_TEXID = 502;  //This is NOT a value in the ASCII table
//TODO: Define constants for each of your Location subclasses
const char CRYSTAL_ID = 'C';
const char ENEMY_ID = 'B';

//Static class variables
string Videogame::message1 = "";
string Videogame::message2 = "";
string Videogame::message3 = "";

Videogame::Videogame()
{
	message1 = "";
	message2 = "";
	message3 = "";

	//Initialize the Eye, Aim, and Up
	Eye[0] = Eye[2] = 0.5; 
	Aim[0] = Aim[2] = Eye[0] + 0.1; //Position the eye looking towards the lower right
	Eye[1] = Aim[1] = 0.4;
	Up[0] = Up[2] = 0.0;
	Up[1] = 1.0;

	MOVEANGLE = 3.14159/4.0;  //45 degrees in radians
	xIN = yIN = 0;

	state = 1;
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
			else if (locationType == "enemy")
			{
				world[r][c] = new VGenemy(ENEMY_ID);
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

	glClearColor(0.2, 0.2, 0.5, 1.0);  //Will be the color of the sky
	
	//Set parameters for how we want to view the scene
	glViewport(0,0, WINDOWWIDTH, WINDOWHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the monitor 
	double aspectRatio = ((double)(WINDOWWIDTH)) / ((double)(WINDOWHEIGHT));
	glFrustum(-0.1, 0.1, -0.1/aspectRatio, 0.1/aspectRatio, 0.1, 1000); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Do OpenGL init stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glLineWidth(1.0); //Controls the thickness of lines
	glColor3f(0.3, 0.3, 0.3);  //The basic color for unlit objects

	//NOTE: the texture IDs are defined in the file constantTexIDs.h
	Texture loader;
	loader.loadTexBMP("images//tree.bmp", TREE_TEXID, addAlpha);
	loader.loadTexBMP("images//trees.bmp", TREES_TEXID, addAlpha);
	loader.loadTexBMP("images//balloon.bmp", ((int)(ENEMY_ID)), addAlpha);
	loader.loadTexBMP("images//crystal.bmp", ((int)(CRYSTAL_ID)), addAlpha);

	//The code below creates the fog effect
	glEnable(GL_FOG);
	GLfloat fogColor[4] = {0.6, 0.6, 0.6, 1.0};  //Makes a gray-like fog
	glFogi(GL_FOG_MODE, GL_LINEAR);  //FOG MODES:  GL_LINEAR, GL_EXP, GL_EXP2
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, 0.1);  //ONLY MATTERS IF FOG IS LINEAR
	glFogf(GL_FOG_END, 2.0);	//ONLY MATTERS IF FOG IS LINEAR

	return true;  //Everything got initialized
}

void Videogame::drawBackground()
{
	double r, c;

	//Draw the grass/ground
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0, 0.4, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(-1.0, 0.0, -1.0);
		glVertex3f(-1.0, 0.0, rows+1);
		glVertex3f(cols+1, 0.0, rows+1);
		glVertex3f(cols+1, 0.0, -1.0);
	glEnd();

	//Draw the surrounding mountains gray mountains with white peaks
	for (r = -1.0; r <= rows + 1; r += rows+2)
	{
		for (c = -1.0; c < cols + 1; c+=1.0)
		{
			glColor3f(0.3, 0.3, 0.3);  //Make the mountains gray
			glBegin(GL_QUADS); //base of mountains
				glVertex3f(-1.0, 0.0, r);
				glVertex3f(cols+1, 0.0, r);
				glVertex3f(cols+1, 1.0, r);
				glVertex3f(-1.0, 1.0, r);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);  //Make the peaks white
			glBegin(GL_TRIANGLES); //peaks of mountains
				glVertex3f(c, 1, r);
				glVertex3f(c+1, 1, r);
				glVertex3f(c+0.5,2, r);
			glEnd();
		}
	}
	for (c = -1.0; c <= cols + 1; c += cols+2)
	{
		for (r = rows+1; r > -1.0; r-=1.0)
		{
			glColor3f(0.3, 0.3, 0.3);  //Make the mountains gray
			glBegin(GL_QUADS); //base of mountains
				glVertex3f(c, 0.0, r+1);
				glVertex3f(c, 0.0, -1.0);
				glVertex3f(c, 1.0, -1.0);
				glVertex3f(c, 1.0, r+1);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);  //Make the peaks white
			glBegin(GL_TRIANGLES); //peaks of mountains
				glVertex3f(c, 1, r);
				glVertex3f(c, 1, r-1);
				glVertex3f(c, 2, r-0.5);
			glEnd();
		}
	}

	//Draw the trees
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	for (r = 0.0; r < rows; r+= 1.0)
	{
		for (c = 0.0; c <= cols; c+= 1.0)
		{
			glBindTexture(GL_TEXTURE_2D, TREES_TEXID);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(c, 0.0, r);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(c, 0.0, r+1);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(c, 1.0, r+1);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(c, 1.0, r);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, TREE_TEXID);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(c-0.5, 0.0, r+0.5);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(c+0.5, 0.0, r+0.5);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(c+0.5, 1.0, r+0.5);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(c-0.5, 1.0, r+0.5);
			glEnd();
		}
	}
	for (r = 0.0; r <= rows; r+= 1.0)
	{
		for (c = 0.0; c < cols; c+= 1.0)
		{
			glBindTexture(GL_TEXTURE_2D, TREES_TEXID);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(c, 0.0, r);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(c+1, 0.0, r);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(c+1, 1.0, r);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(c, 1.0, r);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, TREE_TEXID);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(c+0.5, 0.0, r-0.5);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(c+0.5, 0.0, r+0.5);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(c+0.5, 1.0, r+0.5);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(c+0.5, 1.0, r-0.5);
			glEnd();
		}
	}
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

void Videogame::handleEvent(SDL_Event *theEvent)
{
	switch(theEvent->type)
	{
		case SDL_QUIT: //pressed the 'X' in the Window
		{
			state = 0;
			return;
		}
		case SDL_KEYDOWN:  //Separate events occur for key down and key up
		{
			if (theEvent->key.keysym.sym == ' ') //Try to pop a balloon
			{
				//Determine where the player is located
				int playerRow = ((int)(Eye[2]));  //You can convert the player's position to array indices 
				int playerCol = ((int)(Eye[0]));  //to reference the world array like this

				if (world[playerRow][playerCol]->getSymbol() == ENEMY_ID)
				{
					((Enemy *)(world[playerRow][playerCol]))->setHealth(0);
				}
			}
			else if (theEvent->key.keysym.sym == SDLK_LEFT)
			{
				xIN = -1;
			}
			else if (theEvent->key.keysym.sym == SDLK_RIGHT)
			{
				xIN = 1;
			}
			else if (theEvent->key.keysym.sym == SDLK_UP)
			{
				yIN = 1;
			}
			else if (theEvent->key.keysym.sym == SDLK_DOWN)
			{
				yIN = -1;
			}
			break;
		}
		case SDL_KEYUP:  //stop moving when key comes up
		{
			if (theEvent->key.keysym.sym == SDLK_LEFT || theEvent->key.keysym.sym == SDLK_RIGHT)
			{
				xIN = 0;
			}
			else if (theEvent->key.keysym.sym == SDLK_UP || theEvent->key.keysym.sym == SDLK_DOWN)
			{
				yIN = 0;
			}
			break;
		}
	}
}


void Videogame::updateGame()
{
	const double SCALE_TURN = 1.0;   //Adjust these values to make
	const double SCALE_MOVE = 100.0; //movement seem faster/slower
	int playerRow = ((int)(Eye[2]));  //You can convert the player's position to array indices 
	int playerCol = ((int)(Eye[0]));  //to reference the world array like this
	double rowDecimal = Eye[2] - playerRow;
	double colDecimal = Eye[0] - playerCol;

	//The locations the player can visit are 1 unit in size.  The if statement below makes the player get into the middle of the square before the visit() 
	//method is called for the location.  This makes it possible to enter a square and see what it there before the visit method is called for the item
	if (rowDecimal > .35 && rowDecimal < .65 && colDecimal > .35 && colDecimal < .65) //make sure player is in middle of square before calling visit
	{
		state = world[playerRow][playerCol]->visit(p);
	}

	//Adjust player position based on the arrow keys.
	//Calculate the amount of turn from xIN
	double turn = xIN / (SCALE_TURN);
	turn *= (3.14159/180.0);  //convert to radians
	MOVEANGLE += turn; //We need to add the new turn to previous turns
	//Calculate the amount of movement based on yIN
	double forward = yIN / (SCALE_MOVE);
	double oldEye0 = Eye[0]; //used for collision detection 
	double oldEye2 = Eye[2]; //used for collision detection
	Eye[0] += cos(MOVEANGLE)*forward;
	Eye[2] += sin(MOVEANGLE)*forward;
	if (Eye[2] < 0.15 || Eye[2] >= rows-0.15 || Eye[0] < 0.15 || Eye[0] >= cols-0.15) //trying to move out of bounds
	{
		Eye[0] = oldEye0; Eye[2] = oldEye2;  //restore old eye position 
	}
	Aim[0] = Eye[0] + cos(MOVEANGLE)/10.0;  //Dividing by 10 ensures that the Aim will
	Aim[2] = Eye[2] + sin(MOVEANGLE)/10.0;  //be 1/10 of a unit in front of the Eye
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


	//message3 is used to draw the player's health to the screen
	stringstream out1;  //This is used to convert an int to a string
	out1 << p.getHealth();
	message3 = p.getName() + "'s health is " + out1.str();
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

	gluLookAt(Eye[0],Eye[1],Eye[2], Aim[0],Aim[1],Aim[2], Up[0],Up[1],Up[2]); 

	drawBackground();

	//draw the stuff at the locations
	glColor3f(1.0, 1.0, 1.0);
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (world[r][c]->getSymbol() != ' ') //if it is not a base Location object, then draw its Billboard
			{
				glPushMatrix();
					glTranslatef(c+0.5, 0.3, r+0.5); //Put the image (if any) in the middle of the square
					world[r][c]->draw(); //Go render whatever is appropriate for this location
				glPopMatrix();
			}
		}
	}

	//Draw the text messages.  HUD stands for Heads Up Display
	drawHUD();

	SDL_GL_SwapBuffers();
}

void Videogame::playGame()
{	
	instructions();

	setUpGame();  //Make sure everything is set up for the first level

	if (!init())  //This function (defined above) sets up OpenGL and SDL
	{
		cout << "Not everything was initialized" << endl;
		return;
	}
	SDL_Event events;  //Makes and SDL_Events object that we can use to handle events
	SDL_PollEvent(&events); //This initializes the events object

	message1 = "Use the arrow keys to move.";
	while (state > 0)
	{
		while (SDL_PollEvent(&events))
		{
			handleEvent(&events);
		}
		if (state != 0)
		{
			updateGame();
			drawGame();
		}
	}
	endGame();
}

void Videogame::instructions()
{
	//In this example we use the MessageBoxA function to display the instructions to the user
	string message = "Welcome to the exciting 3D game of Find the Crystals.  In this game you use the arrow keys to navigate around on the game board and find crystals.  ";
	message += "In this version of the game, there are evil balloons that can injure you if you get too close.  You can zap the balloons by pressing the space bar.  ";
	message += "Try to zap the balloons before you run into them to avoid any damage.  When you find the crystals they will increase your health.  Good luck!  ";
	string title = "Find the Crystals";
	MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK);
	
	//Check to see if the user wants to play
	message = "Do you want to play?";
	int answer = MessageBoxA(NULL, message.c_str(), title.c_str(), MB_YESNO);
	if (answer == IDNO) //NOTE: You can also compare against IDYES to see if the the user selects the "YES" button
	{
		endGame();
		exit(0);
	}
}

void Videogame::endGame()
{
	SDL_Quit();
}