/*
	Steve Suh
	h_suh@u.pacific.edu
	Andre Allan Ponce
	a_ponce1@u.pacific.edu

	WE ran out of time.
	sorry

*/

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h> // handling keyboard input
#include <wincon.h> // handling keyboard input as well
#include <random> // for true random
#include <time.h> // for waiting


#include "game.h"
#include "locationdata.h"
#include "linkedList.h"
#include "coordlist.h"
#include "coordnode.h"
#include "floor.h"
#include "tile.h"
#include "player.h"
#include "item.h"
#include "menutext.h"

// @author Andre Allan Ponce
Game::Game() : 
	world(0),
	player(0),
	locations(0),
	state(STATE_PRE_GAME),
	activeText(""){
	// nothing here yet
}

// @author Andre Allan Ponce
// more randomly generating rooms
Location* Game::createRandomRoom(int x, int y, int flor){
	int id;
	id = getRandomNumber(0,locations.getSize());
	id = 0; // debug
	return makeRoom(id,x,y,flor);
}

// @author Andre Allan Ponce
void Game::createWorld(){
	world = new Floor*[WORLD_SIZE];
	for(int i = 0; i < WORLD_SIZE; i++){
		world[i] = 0;
	}
}

void Game::dropOffItem(){
	//int selection = selectItem();
	if(player->getInventory()->getNumKeys() > 0){
		Location* loc = world[player->get_current_floor()-1]->getLoc(player->getBoardLocX(),player->getBoardLocY());
		if(loc->getNumOfKeys() < 3){
			loc->addItem(player->getInventory()->remove_node(Item::ID_KEY));
		}
		else{
			activeText = MenuText::ERROR_NO_ROOM;
		}
	}
	else{
		activeText = MenuText::ERROR_NO_ITEMS;
	}
}


// @author Andre Allan Ponce
// checks the four cardinal spaces directly around player for an item (which was supposed to be symbols)
/*//
int Game::detectItemID(){
	int currPlayerX = player->getRoomLocX();
	int currPlayerY = player->getRoomLocY();
	bool noItem = true;
	Location* currRoom = world[currX][currY];
	for(int i = 1; i < 5; i++){
		cout << "in here" << i << "\n";
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
			cout << finding;
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
//*/

void Game::gameStates(int& old_state, bool& mapPrint, clock_t& startTime){
	switch(state){
	case STATE_EXPLORE:{
		//old_state = STATE_EXPLORE;
		//state = STATE_WAIT;
		break;
	}
	}
}

// @author Andre Allan Ponce
// @author Computergeek01
// url: http://www.cplusplus.com/forum/beginner/75529/
// key codes: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
// true means we moved, false means no move
bool Game::getKeyInput(WORD key){
	int xNew = player->getBoardLocX();
	int yNew = player->getBoardLocY();
	bool move = false;
	switch(key)
    {
	case VK_ESCAPE:{
		break;
	}
    case VK_LEFT:
	case 0x41: // A
	case VK_NUMPAD4:{ // decrement y
		//activeText = "left!\n"; // debug
		//movePlayer(MOVE_LEFT);
		yNew--;
		move = true;
		break;
	}
	case VK_UP:
	case 0x57: // W
	case VK_NUMPAD8:{ // decrement x
		//activeText = "up!\n"; // debug
		//movePlayer(MOVE_UP);
		xNew--;
		move = true;
		break;
	}
	case VK_RIGHT:
	case 0x44: // D
	case VK_NUMPAD6:{ // increment y
		//activeText =  "right!\n"; // debug
		//movePlayer(MOVE_RIGHT);
		yNew++;
		move = true;
		break;
	}
	case VK_DOWN:
	case 0x53: // S
	case VK_NUMPAD2:{ // increment x
		//activeText =  "down!\n"; // debug
		//movePlayer(MOVE_DOWN);
		xNew++;
		move = true;
		break;
	}
	case 0x45:{ // e key // pick up item
		pickUpItem();
		return true;
		break;
	}
	case 0x51:{ // q key // drop off item
		dropOffItem();
		return true;
		break;
	}
	case 0x49: // this was steve as well // i key
		{
			activeText = player->getInventory()->displayInventory();
			return true;
			break;
		}
	default :{
		// we dont move.
		break;
	}
    }
	if(move){
		return movePlayer(xNew,yNew);
	}
	else{
		return false;
	}
}

// @author Andre Allan Ponce
int Game::getRandomNumber(int start, int end){
	int ran;
	try{
		random_device rd;
		ran = (rd() % (end-start));
	}
	catch(...){
		ran = (rand() % (end-start));	
	}
	// remove debug when done 
	// id 0
	return ran;
}
/*

// @author Andre Allan Ponce
// when the player is at the edge of the screen (where the spaces are) we move to the next room
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
//*/
// @author Andre Allan Ponce
Floor* Game::makeFloor(int id){
	Floor* floor = new Floor(id);
	return floor;
}

Location* Game::makeRoom(int id, int x, int y, int flor){
	Location* loc = new Tile(id,x,y,flor); 
	loc->createNewArray(locations.retrieveRoom(id));
	int keyChance = getRandomNumber(0,100);
	std::cout << keyChance;
	if(keyChance < 100){
		loc->addKey();
	}
	return loc;
}


// @author Andre Allan Ponce
// moves the player. invalid moving will be fixed probably.
bool Game::movePlayer(int xMove, int yMove){
	if(xMove >= 0 && yMove >= 0 && xMove < Floor::FLOOR_HEIGHT && yMove < Floor::FLOOR_WIDTH){
		player->setBoardLocX(xMove);
		player->setBoardLocY(yMove);
		int playerFloor = player->get_current_floor()-1;
		if(world[playerFloor]->getLoc(xMove,yMove) == 0){
			world[playerFloor]->setLoc(createRandomRoom(xMove,yMove,playerFloor),xMove,yMove);
			world[playerFloor]->set_room_doors(xMove,yMove,true); // debug
			// door setting should be done in the makeroom method
		}
		return true;
	}
	return false;
}

void Game::pickUpItem(){
	Location* loc = world[player->get_current_floor()-1]->getLoc(player->getBoardLocX(),player->getBoardLocY());
	if(loc->getNumOfKeys() > 0){
		if(player->getInventory()->getNumKeys() < 3){
			player->addItem(loc->getItem(Item::ID_KEY));
		}
		else{
			activeText = MenuText::ERROR_NO_INVENTORY_SPACE;
		}
	}
	else{
		activeText = MenuText::ERROR_NO_ROOM_ITEMS;
	}
}

// @author Andre Allan Ponce
// prepping the first two rooms
void Game::preGameInit(){
	createWorld();
	world[START_FLOOR-1] = makeFloor(START_FLOOR);
	world[START_FLOOR-1]->setLoc(makeRoom(0,START_ROOM_X,START_ROOM_Y,START_FLOOR),START_ROOM_X,START_ROOM_Y);
	world[START_FLOOR-1]->set_room_doors(START_ROOM_X,START_ROOM_Y,true); //the first room should have all open doors
	player = new Player(PLAYER_SYMBOL);
	player->setBoardLocX(START_ROOM_X);
	player->setBoardLocY(START_ROOM_Y);
	player->set_current_floor(START_FLOOR);
	player->createInventory();
	state = STATE_EXPLORE;
}

// @author Andre Allan Ponce
/*
	found a way to change a certain set of chars:
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms683231(v=vs.85).aspx
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682119(v=vs.85).aspx
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682663(v=vs.85).aspx
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx

	(22,22) is the direct center of the map
	the map is 45x45 chars, which works for 5 rooms in either direction

//*/
void Game::printGame(){
	system("CLS"); 
	cout << world[player->get_current_floor()-1]->getNewMap(player->getBoardLocX(),player->getBoardLocY(),player->getSymbol()) << "\n\n";
	cout << activeText << "\n";
}

void Game::printGamePartial(){
	// this should use a Coord_list linked list to print certain characters to screen
	Coord_List* list = world[player->get_current_floor()-1]->getMapPartial(player->getBoardLocX(),player->getBoardLocY(),player->getSymbol());
	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//DWORD numberOfWrites = 0;
	Coord_Node* character = list->remove_node();
	while(character != 0){
		CHAR_INFO replace;
		replace.Char.AsciiChar = character->get_replacement();
		replace.Attributes = 0;
		COORD coordinateSize;
		coordinateSize.X = 1;
		coordinateSize.Y = 1;
		COORD coordinate;
		coordinate.X = character->get_x();
		coordinate.Y = character->get_y();
		SMALL_RECT bound;
		bound.Left = coordinate.X;
		bound.Top = coordinate.Y;
		bound.Right = coordinate.X+coordinateSize.X;
		bound.Bottom = coordinate.Y+coordinateSize.Y;
		WriteConsoleOutput(consoleOut,&replace,coordinateSize,coordinate,&bound);
		delete character;
		character = list->remove_node();
	}
	delete list;
}

// @author Andre Allan Ponce
// reads in room file format:
/*
	# <-- id 
	+-- --+
	|     |
	       
	|     |
	+-- --+
	(Tile DESIGN)

*/

void Game::readInFile(std::string fileName){
	std::ifstream inFile;
	inFile.open(fileName.c_str());
	if(!inFile.good()){
		throw MenuText::ERROR_FILE_NAME;
	}
	int rows = Tile::TILE_HEIGHT;
	int cols = Tile::TILE_WIDTH;
	while(!inFile.eof()){
		int id;
		inFile >> id;
		inFile.ignore(10, '\n');
		cout << id;
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
		locations.fillRoom(id,rows,cols,&tempRoom);
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
	int old_state = 0;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD NumInputs = 0;
	DWORD InputsRead = 0;
	INPUT_RECORD irInput;
	GetNumberOfConsoleInputEvents(hInput, &NumInputs);
	clock_t startTime = clock();
	bool updateMap = false;
	while(running){
		//printGame();
		switch(state){
		case STATE_PRE_GAME:{
			createWorld();
			preGameInit();
			//state = STATE_LEVEL_ONE;
			printGame();
			break;
		}
		case STATE_GAME_FINISH:{
			break;
		}
		case STATE_WAIT:{
			
			if(clock() - startTime > 20){ // it was too fast at one point
				state = old_state;
			}
			//*/
			//Sleep(1*1000);
			//state = old_state;
			break;
		}
		default:{
			if(updateMap){
				printGame();
				//std::cout << "even\n";
				updateMap = false;
			}
			do ReadConsoleInput( hInput, &irInput, 1, &InputsRead );
			while ((irInput.EventType != KEY_EVENT) || irInput.Event.KeyEvent.bKeyDown);
			//ReadConsoleInput(hInput, &irInput, 1, &InputsRead); 
			activeText = "";
			startTime = clock();
			//Location* thisRoom = world[player][currY];
			updateMap = getKeyInput(irInput.Event.KeyEvent.wVirtualKeyCode);
			gameStates(old_state,updateMap,startTime);
			break;
		}
		}
	}
}

/*// unused, check game.h for reason
int Game::selectItem(){
	bool valid;
	system("CLS");
	do{
		std::cout << MenuText::MENU_ITEM_DISPLAY_INVENTORY << "\n";
		std::cout << player->getInventory()->displayInventory(); // already newlines
		std::cout << MenuText::MENU_ITEM_SELECT;
		int selection;
		std::cin >> selection;
		if(selection >= 1 && selection <= 4){
			return selection;
		}
		valid = false;
		std::cout << MenuText::INVALID_MENU_CHOICE;
	}while(!valid);
}//*/