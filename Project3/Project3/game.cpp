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
<<<<<<< HEAD
=======
<<<<<<< HEAD
#include <stdlib.h>
=======
<<<<<<< HEAD
>>>>>>> b070d0743d70b69e31bf8293975c36be22c20d59
#include "room.h"
#include "item.h" 
=======
>>>>>>> 82e96c42889245432fdc5395350a0c76a2f27fc2
#include <time.h> // for waiting
#include "item.h" 
#include "openroom.h"
#include "closedroom.h"
#include "closetroom.h"
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
// Steve Suh
Game::Game() : 
	world(0),
	roomData(), 
	itemData(),
	player(0),
	monster(0),
	state(STATE_PRE_GAME),
	isFinalDoorIn(false),
	currX(START_ROOM_X),
	currY(START_ROOM_X){
		orbInventoryNames[8] =  "Green Orb ",
								"Yellow Orb",
								"Red Orb   ",
								"White Orb ",
								"Black Orb ",
								"Light Orb ",
								"Dark Orb  ",
								"Pale Orb  ";
		orbProb[8] = 3,8,15,30,40,45,50,80;
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
	if(world[currX][currY] == 0){
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
		for(int k = 0; k < WORLD_SIZE; k++){
			world[i][k] = NULL;
		}
	}

}

<<<<<<< HEAD
// @author Andre Allan Ponce
int Game::detectItemID(){
	int currPlayerX = player->getRoomLocX();
	int currPlayerY = player->getRoomLocY();
	bool noItem = true;
	Location* currRoom = world[currX][currY];
	for(int i = 1; i < 5; i++){
		switch(i){
		case MOVE_LEFT:{
			int finding = findItemID(currRoom->getSpaceAt(currPlayerX,currPlayerY-1));
			if(finding >= 0){
				return finding;
			}
			break;
		}
		case MOVE_UP:{
			int finding = findItemID(currRoom->getSpaceAt(currPlayerX-1,currPlayerY));
			if(finding >= 0){
				return finding;
			}
			break;
		}
		case MOVE_RIGHT:{
			int finding = findItemID(currRoom->getSpaceAt(currPlayerX,currPlayerY+1));
			if(finding >= 0){
				return finding;
			}
			break;
		}
		case MOVE_DOWN:{
			int finding = findItemID(currRoom->getSpaceAt(currPlayerX+1,currPlayerY));
			if(finding >= 0){
				return finding;
			}
			break;
		}
		}
	}
	return -1;
}

// @author Andre Allan Ponce
int Game::findItemID(char sym){
	switch(sym){
	case JUNK_SYMBOL:{
		return itemData.ROOMITEM_JUNK;
		break;
	}
	case VASE_SYMBOL:{
		return itemData.ROOMITEM_VASE;
		break;
	}
	case TABLE_SYMBOL:{
		return itemData.ROOMITEM_TABLE;
		break;
	}
	case CHAIR_SYMBOL:{
		return itemData.ROOMITEM_CHAIR;
		break;
	}
	case LAMP_SYMBOL:{
		return itemData.ROOMITEM_LAMP;
		break;
	}
	case BED_SYMBOL:{
		return itemData.ROOMITEM_BED;
		break;
	}
	case CANDLE_SYMBOL:{
		return itemData.ROOMITEM_CANDLE;
		break;
	}
	case DISH_SYMBOL:{
		return itemData.ROOMITEM_DISH;
		break;
	}
	case DUST_SYMBOL:{
		return itemData.ROOMITEM_DUST;
		break;
	}
	case FORK_SYMBOL:{
		return itemData.ROOMITEM_FORK;
		break;
	}
	case TOILET_SYMBOL:{
		return itemData.ROOMITEM_TOILET;
		break;
	}
	case BATHTUB_SYMBOL:{
		return itemData.ROOMITEM_BATHTUB;
		break;
	}
	case MIRROR_SYMBOL:{
		return itemData.ROOMITEM_MIRROR;
		break;
	}
	case BLOOD_SYMBOL:{
		return itemData.ROOMITEM_BLOOD;
		break;
	}
	case CD_SYMBOL:{
		return itemData.ROOMITEM_CD;
		break;
	}
	default:{
		return -1;
		break;
	}
	}
=======
//steve suh
void Game::updateOrbProbability()
{
	int i = 0;
	if(!orbInventory[0]&&!orbInventory[1]&&!orbInventory[2])
	{
	
	}
	for(int i=0;i<8;i++)
	{
		if(orbInventory[i]&&orbProb[i] != INFINITE)
		{
			orbProb[i+1] -= orbProb[i];
			orbProb[i] = INFINITE;
		}
	}

}

void Game::displayInventory()
{
	string invenStr = "";
	for (int i=0;i<8;i++)
	{
		invenStr += "[";
		if(orbInventory[i])
			invenStr += orbInventoryNames[i];
		else
			invenStr += "          ";
		invenStr += "]\n";
	}
	cout << invenStr;
>>>>>>> 82e96c42889245432fdc5395350a0c76a2f27fc2
}


Item* Game::retrieveItem(int id)
{
	Item *i;
	switch(id)
	{
	case 0:
		{
			i = new Junk(JUNK_SYMBOL,id);
			break;
		}
	case 1:
		{
			i = new Vase(VASE_SYMBOL,id);
			break;
		}
	case 2:
		{
			i = new Table(TABLE_SYMBOL,id);
			break;
		}
	case 3:
		{
			i = new Chair(CHAIR_SYMBOL,id);
			break;
		}
	case 4:
		{
			i = new Lamp(LAMP_SYMBOL,id);
			break;
		}
	case 5:
		{
			i = new Bed(BED_SYMBOL,id);
			break;
		}
	case 6:
		{
			i = new Candle(CANDLE_SYMBOL,id);
			break;
		}
	case 7:
		{
			i = new Dish(DISH_SYMBOL,id);
			break;
		}
	case 8:
		{
			i = new Dust(DUST_SYMBOL,id);
			break;
		}
	case 9:
		{
			i = new Fork(FORK_SYMBOL,id);
			break;
		}
	case 10:
		{
			i = new Toilet(TOILET_SYMBOL,id);
			break;
		}
	case 11:
		{
			i = new Bathtub(BATHTUB_SYMBOL,id);
			break;
		}
	case 12:
		{
			i = new Mirror(MIRROR_SYMBOL,id);
			break;
		}
	case 13:
		{
			i = new Blood(BLOOD_SYMBOL,id);
			break;
		}
	case 14:
		{
			i = new Cd(CD_SYMBOL,id);
			break;
		}
	default:
		i = new Junk('d',-1);
	}

	return i;

	//return i;
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
	case 0x45: // e key
		{
<<<<<<< HEAD
			int id = detectItemID();
			if(id >= 0){
				Item* thisItem = retrieveItem(id);
				thisItem->setDescription(itemData.getItemDesc(id));
				thisItem->action();
			}
=======
			int check = 0;
			retrieveItem(detectItemID)->action();
			updateOrbProbability();
			while(check == 0)
			{
				if(rand()%orbProb[i] == 1)
				{
				orbInventory[i] = true;
				check ++;
				}
			}

			break;
		}
	case 0x49:
		{
			displayInventory();
			break;
>>>>>>> 82e96c42889245432fdc5395350a0c76a2f27fc2
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
		inFile.ignore(10, '\n');
		cout << id << rows << cols;
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
void Game::readInItemFile(std::string fileName){
	std::ifstream inFile;
	inFile.open(fileName.c_str());
	if(!inFile.good()){
		throw MenuText::ERROR_FILE_NAME;
	}
	int size;
	inFile >> size;
	inFile.ignore();
	itemData.setSize(size);
	while(!inFile.eof()){
		int id;
		inFile >> id;
		std::string name;
		char symbol;
		inFile >> name;
		inFile >> symbol;
		inFile.ignore();
		std::string line = "";
		getline(inFile,line);
		itemData.createItemEntry(id, name, line);
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
			
			if(clock() - startTime > 20){
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