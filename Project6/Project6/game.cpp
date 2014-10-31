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
	endGameCounter(0),
	isFinalDoorIn(false),
	activeText(""){
	// nothing here yet
}

Game::~Game(){
	deletePlayer();
	deleteWorld();
}

// @author Andre Allan Ponce
// more randomly generating rooms
Location* Game::createRandomRoom(int x, int y, int flor){
	int id;
	//id = getRandomNumber(0,locations.getSize());
	if(x == 0){ // North Edge
		if(y == 0){ // North West Edge
			id = LocationData::TILE_NORTH_WEST;
		}
		else if(y == Floor::FLOOR_WIDTH-1){ // North East Edge
			id = LocationData::TILE_NORTH_EAST;
		}
		else{
			id = LocationData::TILE_NORTH;
		}
	}
	else if(x == Floor::FLOOR_HEIGHT-1){ // South Edge
		if(y == 0){ // South West Edge
			id = LocationData::TILE_SOUTH_WEST;
		}
		else if(y == Floor::FLOOR_WIDTH-1){ // South East Edge
			id = LocationData::TILE_SOUTH_EAST;
		}
		else{
			id = LocationData::TILE_SOUTH;
		}
	}
	else{
		if(y == 0){ // West Edge
			id = LocationData::TILE_WEST;
		}
		else if(y == Floor::FLOOR_WIDTH-1){ // East Edge
			id = LocationData::TILE_EAST;
		}
		else{ // normal room
			id = LocationData::TILE_BASIC;
		}
	}
	// id = 0; // debug
	return makeRoom(id,x,y,flor);
}

// @author Andre Allan Ponce
void Game::createWorld(){
	world = new Floor*[WORLD_SIZE];
	for(int i = 0; i < WORLD_SIZE; i++){
		world[i] = 0;
	}
}

void Game::deletePlayer(){
	if(player != 0 ){
		delete player;
	}
}

void Game::deleteWorld(){
	if(world != 0){
		for(int i = 0; i < WORLD_SIZE; i++){
			if(world[i] != 0){
				delete world[i];
			}
		}
		delete [] world;
	}
}

void Game::dropOffItem(){
	//int selection = selectItem();
	if(player->getInventory()->getNumKeys() > Player::INVENTORY_MIN){
		Location* loc = world[player->get_current_floor()-1]->getLoc(player->getBoardLocX(),player->getBoardLocY());
		if(loc->getNumOfKeys() < Player::INVENTORY_MAX){
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

void Game::gameStates(int& old_state, bool& mapPrint, clock_t& startTime){
	switch(state){
	case STATE_EXPLORE:{
		if(isFinalDoorIn){
			state = STATE_FINAL_DOOR;
		}
		break;
	}
	case STATE_FINAL_DOOR:{
		if(world[player->get_current_floor()-1]->getLoc(finalRoomX,finalRoomY)->getNumOfKeys() == 3){
			state = STATE_GAME_FINISH;
		}
		break;
	}
	default:{
		// we should not be going here
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
		state = STATE_GAME_FINSH_BAD;
		break;
	}
    case VK_LEFT:
	case 0x41: // A
	case VK_NUMPAD4:{ // decrement y
		yNew--;
		move = true;
		break;
	}
	case VK_UP:
	case 0x57: // W
	case VK_NUMPAD8:{ // decrement x
		xNew--;
		move = true;
		break;
	}
	case VK_RIGHT:
	case 0x44: // D
	case VK_NUMPAD6:{ // increment y
		yNew++;
		move = true;
		break;
	}
	case VK_DOWN:
	case 0x53: // S
	case VK_NUMPAD2:{ // increment x
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
	case 0x48:{ // H key // help
		printHelp();
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
		movePlayer(xNew,yNew);
		return true;
	}
	else{
		return false;
	}
}

// @author Andre Allan Ponce
int Game::getRandomNumber(int start, int end){
	int ran;
	try{
		random_device rd; // random_device is true random
		ran = (rd() % (end-start));
	}
	catch(...){
		ran = (rand() % (end-start));	
	}
	return ran;
}

// @author Andre Allan Ponce
Floor* Game::makeFloor(int id){
	Floor* floor = new Floor(id);
	return floor;
}

Location* Game::makeRoom(int id, int x, int y, int flor){
	Location* loc = new Tile(id,x,y,flor); 
	loc->createNewArray(locations.retrieveRoom(id));
	setupDoors(loc,id);
	int chance = getRandomNumber(0,100);
	if(!isFinalDoorIn){
		if(chance <= endGameCounter++){
			loc->setFinalRoom(true);
			isFinalDoorIn = true;
			modeText = MenuText::MAP_FIND_KEYS;
			finalRoomX = x;
			finalRoomY = y;
		}
	}
	if(chance < 10){
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
			//world[playerFloor]->set_room_doors(xMove,yMove,true); // debug
			// door setting should be done in the makeroom method
		}
		return true;
	}
	activeText = MenuText::INVALID_MOVE;
	return false;
}

void Game::pickUpItem(){
	Location* loc = world[player->get_current_floor()-1]->getLoc(player->getBoardLocX(),player->getBoardLocY());
	if(loc->getNumOfKeys() > Player::INVENTORY_MIN){
		if(player->getInventory()->getNumKeys() < Player::INVENTORY_MAX){
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
	// NOT IMPLEMENTED DUE TO ISSUES
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms683231(v=vs.85).aspx
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682119(v=vs.85).aspx
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682663(v=vs.85).aspx
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682022(v=vs.85).aspx

	(22,22) is the direct center of the map
	the map is 35x35 chars, which works for 2 rooms in either direction

//*/
void Game::printGame(){
	system("CLS"); 
	std::cout << world[player->get_current_floor()-1]->getNewMap(player->getBoardLocX(),player->getBoardLocY(),player->getSymbol()) << MenuText::MAP_EDGE_BOTTOM << "\n";
	std::cout << activeText << "\n";
	std::cout << modeText << "\n";
}
/*//
void Game::printGamePartial(){ // not working at the moment
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
//*/
void Game::printHelp(){
	system("CLS");
	std::cout << MenuText::MENU_HELP;
	system("pause");
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
			//createWorld();
			preGameInit();
			modeText = MenuText::MAP_EXPLORE;
			printHelp();
			printGame();
			break;
		}
		case STATE_GAME_FINISH:{
			activeText = MenuText::GAME_WINNER;
			modeText = "";
			printGame();
			system("pause");
			running = false;
			break;
		}
		case STATE_GAME_FINSH_BAD:{
			system("CLS");
			std::cout << MenuText::GAME_QUIT;
			running = false;
			break;
		}
		case STATE_WAIT:{
			if(clock() - startTime > 20){ // it was too fast at one point
				state = old_state;
			}
			break;
		}
		default:{
			if(updateMap){
				//printGamePartial();
				//std::cout << "even\n";
				printGame();
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

void Game::setupDoors(Location* loc, int id){
	if(id != LocationData::TILE_NORTH || id != LocationData::TILE_NORTH_EAST || id != LocationData::TILE_NORTH_WEST){
		loc->set_north_door(true);
	}
	if(id != LocationData::TILE_EAST || id != LocationData::TILE_NORTH_EAST || id != LocationData::TILE_SOUTH_EAST){
		loc->set_east_door(true);
	}
	if(id != LocationData::TILE_SOUTH || id != LocationData::TILE_SOUTH_EAST || id != LocationData::TILE_SOUTH_WEST){
		loc->set_south_door(true);
	}
	if(id != LocationData::TILE_WEST || id != LocationData::TILE_SOUTH_WEST || id != LocationData::TILE_NORTH_WEST){
		loc->set_west_door(true);
	}
}