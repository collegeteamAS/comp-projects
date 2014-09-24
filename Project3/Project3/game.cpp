
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h> // handling keyboard input
#include <wincon.h> // handling keyboard input as well
#include <time.h> // for waiting
#include "openroom.h"
#include "closedroom.h"
#include "closetroom.h"
#include "player.h"
#include "menutext.h"
#include "game.h"


// @author Andre Allan Ponce
Game::Game() : 
	world(0),
	roomData(), 
	player(0),
	monster(0),
	state(STATE_PRE_GAME),
	isFinalDoorIn(false),
	currX(START_ROOM_X),
	currY(START_ROOM_X){
	// nothing here yet
}

// @author Andre Allan Ponce
void Game::changeRoom(int move){
	int nextRoomDoor;
	switch(move){
	case MOVE_LEFT:{
		currY--;
		nextRoomDoor = roomData.DOOR_RIGHT;
		break;
	}
	case MOVE_UP:{
		currX--;
		nextRoomDoor = roomData.DOOR_DOWN;
		break;
	}
	case MOVE_RIGHT:{
		currY++;
		nextRoomDoor = roomData.DOOR_LEFT;
		break;
	}
	case MOVE_DOWN:{
		currX++;
		nextRoomDoor = roomData.DOOR_UP;
		break;
	}
	}
	if(world[currX][currY] == NULL){
		world[currX][currY] = createRandomRoom(currX,currY,nextRoomDoor);
	}
}

// @author Andre Allan Ponce
Location* Game::createRandomRoom(int x, int y, int roomDoor){
	int id;
	bool hasNoDoor = true;
	do{
		id = getRandomNumber();
		if(id == roomData.ROOM_LIVINGROOM && isFinalDoorIn){ // thats the final room, cant have two of those
			hasNoDoor = false;
		}
		else if(roomData.retrieveDoorSpot(id,roomDoor) > 0){
			hasNoDoor = false;
		}
	}while(hasNoDoor);
	if(id == roomData.ROOM_LIVINGROOM){
		isFinalDoorIn = true;
	}
	return makeRoom(id,x,y);
}

// @author Andre Allan Ponce
Location* Game::createRoom(int id, int x, int y){
	int h = roomData.retrieveRoomSize(id,RoomData::DIMENSION_ROW);
	int w = roomData.retrieveRoomSize(id,RoomData::DIMENSION_COL);
	switch(id){
	case RoomData::ROOM_LIVINGROOM :
	case RoomData::ROOM_KITCHEN :
	case RoomData::ROOM_DININGROOM :
	case RoomData::ROOM_HALLWAY_DARK :
	case RoomData::ROOM_HALLWAY_BLOODY :
	case RoomData::ROOM_HALLWAY :{
		return new OpenRoom(id,x,y,h,w); // no closet, multiple doors
		break;
	}
	case RoomData::ROOM_BEDROOM :
	case RoomData::ROOM_BASEMENT :{
		return new ClosetRoom(id,x,y,h,w); // closet, one door
		break;
	}
	case RoomData::ROOM_GARAGE :
	case RoomData::ROOM_BATHROOM :
	case RoomData::ROOM_ATTIC :{
		return new ClosedRoom(id,x,y,h,w); // no closet, one door
		break;
	}
	case RoomData::ROOM :
	default : {
		// return Room(id,x,y,h,w,true,false); // debug
		return new Location(id,x,y,h,w,false,false);
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
void Game::getKeyInput(WORD key, Location* currRoom){
	switch(key)
    {
	case VK_ESCAPE:{
		break;
	}
    case VK_LEFT:
	case VK_NUMPAD4:{
		std::cout << "left!\n";
		movePlayer(MOVE_LEFT, currRoom);
		break;
	}
	case VK_UP:
	case VK_NUMPAD8:{
		std::cout << "up!\n";
		movePlayer(MOVE_UP, currRoom);
		break;
	}
	case VK_RIGHT:
	case VK_NUMPAD6:{
		std::cout << "right!\n";
		movePlayer(MOVE_RIGHT, currRoom);
		break;
	}
	case VK_DOWN:
	case VK_NUMPAD2:{
		std::cout << "down!\n";
		movePlayer(MOVE_DOWN, currRoom);
		break;
	}
	default :{
		// we dont move.
		break;
	}
    } 
}

// @author Andre Allan Ponce
int Game::getRandomNumber(){
	srand(time(NULL));
	return (rand() % roomData.getSize()-1) +1;
}

// @author Andre Allan Ponce
int Game::isLocAtEdge(int x, int y, Location* currRoom){
	if(x == 0){
		return MOVE_UP;
	}
	else if(y == 0){
		return MOVE_LEFT;
	}
	else if(x == currRoom->getHeight()-1){
		return MOVE_DOWN;
	}
	else if(y == currRoom->getWidth()-1){
		return MOVE_RIGHT;
	}
	else{
		//cout << "in here?\n";
		return -1; // we are not at the edge
	}
}

// @author Andre Allan Ponce
Location* Game::makeRoom(int id, int x, int y){
	Location* room = createRoom(id,x,y);
	room->fillArray(roomData.retrieveRoom(id));
	return room;
}

// @author Andre Allan Ponce
// we only go to this if we actually move
void Game::movePlayer(int move, Location* currRoom){
	int xOld = player->getRoomLocX();
	int yOld = player->getRoomLocY();
	cout << "X:" << currX << "," << currY << "\n";
	cout << "xr:" << xOld << "," << yOld << "\n";
	//int xNew, yNew;
	switch(move){
	case MOVE_LEFT:{
		player->moveLeft();
		break;
	}
	case MOVE_UP:{
		player->moveUp();
		break;
	}
	case MOVE_RIGHT:{
		player->moveRight();
		break;
	}
	case MOVE_DOWN:{
		player->moveDown();
		break;
	}
	}
	if(currRoom->movePlayer(xOld,yOld,PLAYER_SYMBOL,player->getRoomLocX(),player->getRoomLocY())){
		int xNewPlay = player->getRoomLocX();
		int yNewPlay = player->getRoomLocY();
		if(isLocAtEdge(xNewPlay,yNewPlay,currRoom) > 0){
			currRoom->resetSpace(xNewPlay,yNewPlay,currRoom->EMPTY_SPACE);
			changeRoom(move);
			player->setBoardLocX(currX);
			player->setBoardLocY(currY);
			placePlayerInNewRoom(move, player, PLAYER_SYMBOL);
		}
	}
	else{
		player->setRoomLocX(xOld);
		player->setRoomLocY(yOld);
	}
}

// @author Andre Allan Ponce
void Game::placePlayerInNewRoom(int move, Player* play, char sym){
	Location* newRoom = world[currX][currY];
	int id = newRoom->getRoomID();
	int xNew, yNew;
	switch(move){
	case MOVE_LEFT:{
		xNew = roomData.retrieveDoorSpot(id,roomData.DOOR_RIGHT);
		yNew = newRoom->getWidth()-2;
		break;
	}
	case MOVE_UP:{
		xNew = newRoom->getHeight()-2;
		yNew = roomData.retrieveDoorSpot(id,roomData.DOOR_DOWN);
		break;
	}
	case MOVE_RIGHT:{
		xNew = roomData.retrieveDoorSpot(id,roomData.DOOR_LEFT);
		yNew = 1;
		break;
	}
	case MOVE_DOWN:{
		xNew = 1;
		yNew = roomData.retrieveDoorSpot(id,roomData.DOOR_UP);
		break;
	}
	}
	newRoom->setPlayer(xNew,yNew,sym);
	play->setRoomLocX(xNew);
	play->setRoomLocY(yNew);
}

// @author Andre Allan Ponce
void Game::preGameInit(){
	world[currX][currY] = makeRoom(RoomData::ROOM_BEDROOM,currX,currY);
	std::cout << "here\n";
	world[currX][currY]->setPlayer(START_PLAYER_X,START_PLAYER_Y,PLAYER_SYMBOL);
	std::cout << "hree2\n";
	world[currX][START_ROOM_Y] = makeRoom(RoomData::ROOM_HALLWAY,currX,START_ROOM_Y);
	player = new Player(PLAYER_SYMBOL);
	player->setBoardLocX(currX);
	player->setBoardLocY(currY);
	player->setRoomLocX(START_PLAYER_X);
	player->setRoomLocY(START_PLAYER_Y);
	state = STATE_LEVEL_ONE;
}

void Game::printGame(){
	system("CLS");
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
			//std::cout << line << "\n";
			for(int k = 0; k < cols; k++){
				tempRoom[i][k] = line[k];
			}
		}
		roomData.fillRoom(id,rows,cols,tempRoom);
		//roomData
		for(int i = 0; i < rows; i++){
			delete [] tempRoom[i];
		}
		delete [] tempRoom;
	}
	inFile.close();
}

// @author Andre Allan Ponce
// @author Computergeek01 (for the keyboard input stuff)
// @author Duoas (for more keyboard input stuff)
// url: http://www.cplusplus.com/forum/beginner/75529/
// url: http://www.cplusplus.com/forum/articles/7312/#msg33734
void Game::runGame(){
	bool running = true;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD NumInputs = 0;
	DWORD InputsRead = 0;
	INPUT_RECORD irInput;
	GetNumberOfConsoleInputEvents(hInput, &NumInputs);
	int old_state = 0;
	clock_t startTime = clock();
	while(running){
		//printGame();
		switch(state){
		case STATE_PRE_GAME:{
			createWorld();
			preGameInit();
			state = STATE_LEVEL_ONE;
			break;
		}
		case STATE_GAME_FINISH:{
			break;
		}
		case STATE_WAIT:{
			
			if(clock() - startTime > 100){
				state = old_state;
			}
			//*/
			//Sleep(1*1000);
			//state = old_state;
			break;
		}
		default:{
			printGame();
			do ReadConsoleInput( hInput, &irInput, 1, &InputsRead );
			while ((irInput.EventType != KEY_EVENT) || irInput.Event.KeyEvent.bKeyDown);
			//ReadConsoleInput(hInput, &irInput, 1, &InputsRead); 
			startTime = clock();
			Location* thisRoom = world[currX][currY];
			getKeyInput(irInput.Event.KeyEvent.wVirtualKeyCode, thisRoom);
			switch(state){
			case STATE_LEVEL_ONE:{
				old_state = STATE_LEVEL_ONE;
				state = STATE_WAIT;
				break;
			}
			}
			break;
		}
		}
	}
}