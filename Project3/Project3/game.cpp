/*
	Steve Suh
	h_suh@u.pacific.edu
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
*/

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h> // handling keyboard input
#include <wincon.h> // handling keyboard input as well
#include "room.h"
#include "item.h" 
#include "player.h"
#include "menutext.h"
#include "game.h"

#include "junk.h"
#include "vase.h"
#include "table.h"
#include "chair.h"
#include "lamp.h"
#include "bed.h"
#include "candle.h"
#include "dish.h"
#include "dust.h"
#include "fork.h"
#include "toilet.h"
#include "bathtub.h"
#include "mirror.h"
#include "blood.h"
#include "cd.h"

// @author Andre Allan Ponce
Game::Game() : 
	world(0),
	roomData(), 
	player(0),
	monster(0),
	state(STATE_PRE_GAME),
	currX(START_ROOM_X),
	currY(START_ROOM_X){
	// nothing here yet
}

// @author Andre Allan Ponce
Room* Game::createRoom(int id, int x, int y){
	int h = roomData.retrieveRoomSize(id,RoomData::DIMENSION_ROW);
	int w = roomData.retrieveRoomSize(id,RoomData::DIMENSION_COL);
	switch(id){
	case RoomData::ROOM_LIVINGROOM :
	case RoomData::ROOM_KITCHEN :
	case RoomData::ROOM_DININGROOM :
	case RoomData::ROOM_HALLWAY_DARK :
	case RoomData::ROOM_HALLWAY_BLOODY :
	case RoomData::ROOM_HALLWAY :{
		return new Room(id,x,y,h,w,false,false); // no closet, multiple doors
		break;
	}
	case RoomData::ROOM_BEDROOM :
	case RoomData::ROOM_BASEMENT :{
		return new Room(id,x,y,h,w,true,true); // closet, one door
		break;
	}
	case RoomData::ROOM_GARAGE :
	case RoomData::ROOM_BATHROOM :
	case RoomData::ROOM_ATTIC :{
		return new Room(id,x,y,h,w,false,true); // no closet, one door
		break;
	}
	case RoomData::ROOM :
	default : {
		// return Room(id,x,y,h,w,true,false); // debug
		return new Room(id,x,y,h,w,false,false);
		break;
	}
	}
}

// @author Andre Allan Ponce
void Game::createWorld(){
	world = new Location**[WORLD_SIZE];
	for(int i = 0; i < WORLD_SIZE; i++){
		world[i] = new Location*[WORLD_SIZE];
	}
}


bool isEmpty()
{
	if(
}

Item* retrieveItem(int id)
{
	Item *i;
	switch(id)
	{
	case 0:
		{
			i = new Junk();
			break;
		}
	case 1:
		{
			i = new Vase();
			break;
		}
	case 2:
		{
			i = new Table();
			break;
		}
	case 3:
		{
			i = new Chair();
			break;
		}
	case 4:
		{
			i = new Lamp();
			break;
		}
	case 5:
		{
			i = new Bed();
			break;
		}
	case 6:
		{
			i = new Candle();
			break;
		}
	case 7:
		{
			i = new Dish();
			break;
		}
	case 8:
		{
			i = new Dust();
			break;
		}
	case 9:
		{
			i = new Fork();
			break;
		}
	case 10:
		{
			i = new Toilet();
			break;
		}
	case 11:
		{
			i = new Bathtub();
			break;
		}
	case 12:
		{
			i = new Mirror();
			break;
		}
	case 13:
		{
			i = new Blood();
			break;
		}
	case 14:
		{
			i = new Cd();
			break;
		}
	}

	return i;
}
// @author Computergeek01
// url: http://www.cplusplus.com/forum/beginner/75529/
void Game::getKeyInput(INPUT_RECORD* irIn, Room* currRoom){
	switch(irIn->Event.KeyEvent.wVirtualKeyCode)
    {
	case VK_ESCAPE:{
		break;
	}
    case VK_LEFT:
	case VK_NUMPAD4:{
		std::cout << "left!\n";
		//currX--;
		int xOld = 
		break;
	}
	case VK_UP:
	case VK_NUMPAD8:{
		std::cout << "up!\n";
		//currY--;
		player->moveRight();
		break;
	}
	case VK_RIGHT:
	case VK_NUMPAD6:{
		std::cout << "right!\n";
		//currX++;
		break;
	}
	case VK_DOWN:
	case VK_NUMPAD2:{
		std::cout << "down!\n";
		//currY++;
		break;
	}
	case 0x45:
		{
			player->detectItemID().retrieveItem()->action();
		}
	default :{
		// we dont move.
		break;
	}
    } 
}

// @author Andre Allan Ponce
void Game::preGameInit(){
	Room* startRoom = createRoom(RoomData::ROOM_BEDROOM,currX,currY);
	startRoom->setPlayer(START_PLAYER_X,START_PLAYER_Y,PLAYER_SYMBOL);
	world[currX][currY] = startRoom;
	world[currX][START_ROOM_Y] = createRoom(RoomData::ROOM_HALLWAY,currX,START_ROOM_Y);
	player = new Player(PLAYER_SYMBOL);
	player->setBoardLocX(currX);
	player->setBoardLocY(currY);
	player->setRoomLocX(START_PLAYER_X);
	player->setRoomLocY(START_PLAYER_Y);
	state = STATE_LEVEL_ONE;
}

void Game::printGame(){
	cout << world[currX][currY]->draw() << "\n";
}

// @author Andre Allan Ponce
void Game::readInFile(std::string fileName){
	std::ifstream inFile;
	inFile.open(fileName.c_str());
	if(!inFile.good()){
		throw MenuText::ERROR_FILE_NAME;
	}
	while(!inFile.eof()){
		int id, rows, cols;
		inFile >> id;
		inFile >> rows;
		inFile >> cols;
		inFile.ignore();
		char** tempRoom = new char*[rows];
		for(int i = 0; i < rows; i++){
			std::string line = "";
			tempRoom[i] = new char[cols];
			std::getline(inFile, line);
			strcpy_s(tempRoom[i], cols, line.c_str()); // copes char array to char array (or string to string);
		}
		roomData.fillRoom(id,rows,cols,tempRoom);
		for(int i = 0; i < rows; i++){
			delete [] tempRoom[i];
		}
		delete [] tempRoom;
	}
	inFile.close();
}

// @author Andre Allan Ponce
// @author Computergeek01 (for the keyboard input stuff)
// url: http://www.cplusplus.com/forum/beginner/75529/
void Game::runGame(){
	bool running = true;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD NumInputs = 0;
	DWORD InputsRead = 0;
	INPUT_RECORD* irInput = new INPUT_RECORD;
	GetNumberOfConsoleInputEvents(hInput, &NumInputs);
	while(running){
		ReadConsoleInput(hInput, irInput, 1, &InputsRead);
		switch(state){
		case STATE_PRE_GAME :{
			createWorld();
			preGameInit();
			printGame();
		}
		case STATE_LEVEL_ONE :{
			Room* thisRoom = *world[currX][currY];
			
			getKeyInput(irInput); // affects the currX, currY
		}
		}
	}
}