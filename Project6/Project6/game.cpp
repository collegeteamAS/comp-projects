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
#include "coordlist.h"
#include "coordnode.h"
#include "floor.h"
#include "tile.h"
#include "player.h"
#include "menutext.h"

// @author Andre Allan Ponce
Game::Game() : 
	world(0),
	player(0),
	locations(0),
	state(STATE_PRE_GAME),
	activeText("debug"){
	// nothing here yet
}

// @author Andre Allan Ponce
// moves from one ROOOM ( or Location) to the next
/*
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
		world[currX][currY] = createRandomRoom(currX,currY,nextRoomDoor); // RANDOMLY generated rooms
	}
}
//*/
// @author Andre Allan Ponce
// more randomly generating rooms
Location* Game::createRandomRoom(int x, int y, int flor){
	int id;
	id = getRandomNumber();
	id = 0; // debug
	return makeRoom(id,x,y,flor);
}

// @author Andre Allan Ponce
/*
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
//*/
// @author Andre Allan Ponce
void Game::createWorld(){
	world = new Floor*[WORLD_SIZE];
	for(int i = 0; i < WORLD_SIZE; i++){
		world[i] = 0;
	}
}


// @author Andre Allan Ponce
// checks the four cardinal spaces directly around player for an item (which was supposed to be symbols)
/*
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

// @author Andre Allan Ponce
/*
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
}

//steve suh
void Game::updateOrbProbability()
{
	int i = 0;
	for(int i=0;i<8;i++)
	{
		activeText = "morethanjust orb\n";
		if(orbInventory[i]&&orbProb[i] < 999999)
		{
			activeText = "littlemore\n";
			orbProb[i+1] -= orbProb[i];
			orbProb[i] = 999999;

		}
	}
	//return -1;
}


//Steve Suh
/*
void Game::displayInventory()
{
	string invenStr = "";
	for (int i=0;i<8;i++)
	{
		invenStr += "[";
		if(orbInventory[i])
			invenStr += orbInventoryNames[i];
		else
			invenStr += "xxxxxxxxxx";
		invenStr += "]\n";
	}
	cout << invenStr;

}

//Steve Suh
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
//*/

void Game::gameStates(int& old_state, bool& mapPrint, clock_t& startTime){
	switch(state){
	case STATE_EXPLORE:{
		old_state = STATE_EXPLORE;
		state = STATE_WAIT;
		break;
	}
	}
}

// @author Andre Allan Ponce
// @author Computergeek01
// url: http://www.cplusplus.com/forum/beginner/75529/
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
	case VK_NUMPAD4:{ // decrement y
		activeText = "left!\n"; // debug
		//movePlayer(MOVE_LEFT);
		yNew--;
		move = true;
		break;
	}
	case VK_UP:
	case VK_NUMPAD8:{ // decrement x
		activeText = "up!\n"; // debug
		//movePlayer(MOVE_UP);
		xNew--;
		move = true;
		break;
	}
	case VK_RIGHT:
	case VK_NUMPAD6:{ // increment y
		activeText =  "right!\n"; // debug
		//movePlayer(MOVE_RIGHT);
		yNew++;
		move = true;
		break;
	}
	case VK_DOWN:
	case VK_NUMPAD2:{ // increment x
		activeText =  "down!\n"; // debug
		//movePlayer(MOVE_DOWN);
		xNew++;
		move = true;
		break;
	}
	case 0x41: // a key // this was steve
		{
			/*activeText = "ea \n";
			int i = 0;
			int id = detectItemID();
			if(id >= 0){
				Item* thisItem = retrieveItem(id);
				thisItem->setDescription(itemData.getItemDesc(id));
				thisItem->action();
				int check = 0;
				while(check == 0 && i<8)
				{
					activeText = "orb\n";
					int run = rand()%orbProb[i];
					cout << run;
					if( run == 1)
					{
						orbInventory[i] = true;
						updateOrbProbability();
						check++;
					}
				i++;
				}
			}
			//*/

			break;
		}


			
	case 0x49: // this was steve as well
		{
			//displayInventory();
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
int Game::getRandomNumber(){
	int ran;
	try{
		random_device rd;
		ran = (rd() % locations.getSize()-1)+1;
	}
	catch(...){
		ran = (rand() % locations.getSize()-1) +1;	
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
	return loc;
}


// @author Andre Allan Ponce
// moves the player. invalid moving will be fixed probably.
bool Game::movePlayer(int xMove, int yMove){
	//cout << "X:" << currX << "," << currY << "\n"; // debug
	//cout << "xr:" << xMove << "," << yMove << "\n"; // debug
	//int xNew, yNew;
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

/*
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
//*/

// @author Andre Allan Ponce
// prepping the first two rooms
void Game::preGameInit(){
	createWorld();
	world[START_FLOOR-1] = makeFloor(START_FLOOR);
	//std::cout << "here\n";
	//world[currX][currY]->setPlayer(START_PLAYER_X,START_PLAYER_Y,PLAYER_SYMBOL);
	world[START_FLOOR-1]->setLoc(makeRoom(0,START_ROOM_X,START_ROOM_Y,START_FLOOR),START_ROOM_X,START_ROOM_Y);
	//std::cout << "hree2\n";
	//world[currX][START_ROOM_Y] = makeRoom(RoomData::ROOM_HALLWAY,currX,START_ROOM_Y);
	world[START_FLOOR-1]->set_room_doors(START_ROOM_X,START_ROOM_Y,true); //the first room should have all open doors
	//currX = START_ROOM_X;
	//currY = START_ROOM_Y;
	player = new Player(PLAYER_SYMBOL);
	player->setBoardLocX(START_ROOM_X);
	player->setBoardLocY(START_ROOM_Y);
	player->set_current_floor(START_FLOOR);
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
	+--- ---+
	|       |
	         
	|       |
	+--- ---+
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
/*
	reads in items file (not much use, though)
	<id> <name>
	<description
//*/
/*
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
//*/
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
			startTime = clock();
			//Location* thisRoom = world[player][currY];
			updateMap = getKeyInput(irInput.Event.KeyEvent.wVirtualKeyCode);
			gameStates(old_state,updateMap,startTime);
			break;
		}
		}
	}
}
