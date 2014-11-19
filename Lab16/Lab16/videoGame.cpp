/*//
	Andre Allan Ponce
	Steve Suh
	-> modified version of Lab16 videoGame.cpp
//*/
#include "videogame.h"
#include "texture.h"

#include "VGkey.h"
#include "VGdoor.h"
#include <SDL.h>
#include <Windows.h>  //Must include this here to get it to compile
#include <glut.h>  //includes gl.h and glu.h
#include <iostream>
#include <string>
#include <sstream>

//Static class variables
string Videogame::message1 = "";
string Videogame::message2 = "";
string Videogame::message3 = "";

Videogame::Videogame() : Game()
{

}

void Videogame::setUpGame()
{
	int r, c;
	string locationType;

	ifstream dataFile(MenuText::FILE_NAME_LAYOUT);

	if (!dataFile)
	{
		cout << MenuText::ERROR_FILE_CANNOT_READ << "\n";
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
		
			if (locationType.c_str()[0] == Key::SYMBOL_KEY)
			{
				world[r][c] = new VGkey(ID_KEY);
			}
			else if(locationType.c_str()[0] == Door::SYMBOL_DOOR){
				world[r][c] = new VGdoor(ID_DOOR);
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

//Initializes SDL and OpenGL
bool Videogame::init()
{
	display = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if ((display = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL )) == NULL)
	{
		return false;
	}

	glClearColor(0.3, 0.3, 0.3, 1.0);  //Will be the color of the background
	
	//Set parameters for how we want to view the scene
	glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(WINDOW_WIDTH)) / ((double)(WINDOW_HEIGHT));
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
	loader.loadTexBMP(MenuText::FILE_NAME_IMAGE_DOOR.c_str(), ID_DOOR, addAlpha);  // The door!
	loader.loadTexBMP(MenuText::FILE_NAME_IMAGE_PLAYER.c_str(), ID_PLAYER, addAlpha);  // the player
	loader.loadTexBMP(MenuText::FILE_NAME_IMAGE_KEY.c_str(), ID_KEY, addAlpha);

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
	double aspectRatio = ((double)(WINDOW_WIDTH)) / ((double)(WINDOW_HEIGHT));
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
		renderBitMap(ID_PLAYER);
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
			return ACTION_BLANK;
		}
		case SDL_KEYDOWN:
		{
			if (theEvent->key.keysym.sym == SDLK_LEFT || theEvent->key.keysym.sym == SDLK_a)
			{ 
				return ACTION_LEFT; 
			}
			else if (theEvent->key.keysym.sym == SDLK_RIGHT || theEvent->key.keysym.sym == SDLK_d)
			{ 
			   return ACTION_RIGHT; 
			} 
			else if (theEvent->key.keysym.sym == SDLK_UP || theEvent->key.keysym.sym == SDLK_w)
			{ 
			   return ACTION_UP;
			}
			else if (theEvent->key.keysym.sym == SDLK_DOWN || theEvent->key.keysym.sym == SDLK_s)
			{ 
			   return ACTION_DOWN;
			}
			/*//
			else if (theEvent->key.keysym.sym == SDLK_e){ // pick up
				return 'e';
			}
			else if (theEvent->key.keysym.sym == SDLK_q){ // drop item
				return 'q';
			}
			//*/
			else if (theEvent->key.keysym.sym == SDLK_ESCAPE){
				endGame();
				exit(0);
				return ACTION_BLANK;
			}
		}
	 } 
	 return ACTION_NOTHING;
}

void Videogame::playGame()
{
	int state = 1;
	char choice = ACTION_NOTHING;

	instructions();
	setUpGame();  //Make sure everything is set up for the first level

	if (!init())  //This function (defined above) sets up OpenGL and SDL
	{
		cout << MenuText::ERROR_FAILED_INITIALIZE << "\n";
		return;
	}
	SDL_Event events;  //Makes and SDL_Events object that we can use to handle events
	SDL_PollEvent(&events); //This initializes the events object

	while (state != 10) //the game continues as long as state is not 10 (which for now is forever)
	{
		do
		{
			choice = ACTION_NOTHING;
			message1 = MenuText::MENU_HELP_SHORT;
			drawGame();
			while (SDL_PollEvent(&events)) 
			{
				choice = handleEvent(&events);
			}

			if (choice == ACTION_UP && playerRow > 0)  //Check to see if the player pressed 'u'
			{
				playerRow--;					//if the player pressed 'u' subtract one from his/her row
			}
			else if(choice == ACTION_DOWN && playerRow < rows-1){
				playerRow++;
			}
			else if(choice == ACTION_RIGHT && playerCol < cols-1){
				playerCol++;
			}
			else if(choice == ACTION_LEFT && playerCol > 0){
				playerCol--;
			}
			/*//
			else if(choice == 'e'){
				message2 = "yeah nothing"
				drawGame();
				Sleep(500);
			}
			else if(choice == 'q'){
				message2 = "what you expect";
				drawGame();
				Sleep(500);
			}
			//*/
			else if (choice != ACTION_NOTHING)  //User made an illegal move
			{
				choice = ACTION_NOTHING;
				message2 = MenuText::ERROR_INVALID_INPUT;
				drawGame();
				Sleep(500);
			}

		} while (choice == ACTION_NOTHING);  //stays in this loop until the user presses a key

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