
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h> // handling keyboard input
#include <wincon.h> // handling keyboard input as well
#include "room.h"
#include "player.h"
#include "menutext.h"
#include "game.h"


// @author Andre Allan Ponce
Game::Game() : 
	world(0),
	roomData(), 
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