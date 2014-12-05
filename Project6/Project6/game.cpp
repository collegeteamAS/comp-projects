/*
	Steve Suh
	h_suh@u.pacific.edu
	Andre Allan Ponce
	a_ponce1@u.pacific.edu

*/

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <Windows.h> // handling keyboard input
#include <wincon.h> // handling keyboard input as well
#include <random> // for true random
#include <time.h> // for waiting
#include <vector>


#include "game.h"
#include "locationdata.h"
#include "linkedList.h"
#include "coordlist.h"
#include "coordnode.h"
#include "floor.h"
#include "tile.h"
#include "tile_stairs.h"
#include "tile_exit.h"
#include "player.h"
#include "item.h"
#include "menutext.h"

// @author Andre Allan Ponce
Game::Game() : 
	world(0),
	player(0),
	numberOfFloors(0),
	locations(0),
	state(STATE_PRE_GAME),
	isFinalDoorIn(false),
	activeText(""){
	// nothing here yet
}

Game::~Game(){
	//deletePlayer();
	deleteWorld();
}

// ==== private methods ====

bool Game::arePreviousStairsUp(int x, int y, int floor){
	Floor* previousFloor = (*world)[floor];
	if(previousFloor->getStairsDown() == 0){ // no downstairs, we only have upstairs
		return true;
	}
	else if(previousFloor->getStairsUp() == 0){ // no upstairs, we only have downstairs
		return false;
	}
	else{
		return (previousFloor->getStairsUp()->getCoordinateX() == x && previousFloor->getStairsUp()->getCoordinateY() == y);
	}
}

bool Game::canMoveFrom(int x, int y){
	switch(state){
	case STATE_MOVE_LEFT:{ // we leave this room from the west
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_west_door()){ // if this is open
			return true;
		}
		break;
	}
	case STATE_MOVE_UP:{ // we leave this room from the north
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_north_door()){
			return true;
		}
		break;
	}
	case STATE_MOVE_RIGHT:{ // we leave this room from the east
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_east_door()){
			return true;
		}
		break;
	}
	case STATE_MOVE_DOWN:{ // we leave this room from the south
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_south_door()){
			return true;
		}
		break;
	}
	default:{ // we should not be going here
		break;
	}
	}
	return false;
}

bool Game::canMoveTo(int x, int y){
	switch(state){
	case STATE_MOVE_LEFT:{ // we enter this room from the east
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_east_door()){ // if this is open
			return true;
		}
		break;
	}
	case STATE_MOVE_UP:{ // we enter this room from the south
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_south_door()){
			return true;
		}
		break;
	}
	case STATE_MOVE_RIGHT:{ // we enter this room from the west
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_west_door()){
			return true;
		}
		break;
	}
	case STATE_MOVE_DOWN:{ // we enter this room from the north
		if((*world)[player->getCurrentFloor()]->getLoc(x,y)->get_north_door()){
			return true;
		}
		break;
	}
	default:{ // we should not be going here
		break;
	}
	}
	return false;
}

void Game::connectStairs(int previousFloor, int nextFloor, bool goingUp){
	StairsTile* previous;
	StairsTile* next;
	if(goingUp){
		previous = (*world)[previousFloor]->getStairsUp();
		next = (*world)[nextFloor]->getStairsDown();
	}
	else{
		previous = (*world)[previousFloor]->getStairsDown();
		next = (*world)[nextFloor]->getStairsUp();
	}
	previous->setNextFloor(next);
	next->setNextFloor(previous);
}

// @author Andre Allan Ponce
// more randomly generating rooms
void Game::createRandomRoom(int x, int y, int flor){
	int id = tileIDRandomizer(x,y);
	if(!hasValidDoor(id)){
		id = 0; // if the random room is invalid, we are just gonna make a basic room
	}
	int chance = getRandomNumber(0,100); // out of 100
	Floor* currentFloor = (*world)[player->getCurrentFloor()];
	if(currentFloor->getNumberOfCreatedRooms() >= Floor::STAIRS_GENERATION_THRESHOLD && chance < currentFloor->getStairCount()){
		if(!currentFloor->hasStairsUp()){
			makeStairs(currentFloor,id,x,y,true);
			return;
		}
		else if(!currentFloor->hasStairsDown()){
			makeStairs(currentFloor,id,x,y,false);
			return;
		}
	}
	Location* loc;
	if(!currentFloor->isScoreRoomHere() && chance < currentFloor->getScoreCounter()){
		loc = makeRoomScore(id,x,y,flor);
		currentFloor->setScoreRoomHere(true);
	}
	else{
		loc =  makeRoom(id,x,y,flor);
	}
	if(chance < Floor::KEY_ADD_THRESHOLD){
		loc->addKey(); // these have 0 purpose rightnow
	}
}

// @author Andre Allan Ponce
void Game::createWorld(){
	world = new std::vector<Floor*>();
	for(int i = 0; i < WORLD_SIZE; i++){
		world->push_back(makeFloor(i));
	}
}

void Game::deletePlayer(){
	if(player != 0 ){
		delete player;
	}
}

void Game::deleteWorld(){
	for(int i = 0; i < WORLD_SIZE; i++){
		delete world->at(i);
	}
}

int Game::distanceFromEdge(int coordinate){
	if(coordinate > START_ROOM_X){
		return (START_ROOM_X - (1+std::abs(START_ROOM_X - coordinate)));
	}
	return (START_ROOM_X - (std::abs(START_ROOM_X - coordinate)));
}

void Game::dropOffItem(){
	//int selection = selectItem();
	if(player->getInventory()->getNumKeys() > Player::INVENTORY_MIN){
		Location* loc = (*world)[player->getCurrentFloor()]->getLoc(player->getCurrentX(),player->getCurrentY());
		if(loc->getNumOfKeys() < Player::INVENTORY_MAX){
			loc->addItem(player->getInventory()->remove_node(Item::ID_KEY));
		}
		else{
			player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::ERROR_NO_ROOM);
		}
	}
	else{
		player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::ERROR_NO_ITEMS);
	}
}

bool Game::edgeChanceMaker(int distance){
	switch(distance){
	case 0:{
		return true;
		break;
	}
	case 1:{
		return isThisAnEdgeNow(CHANCE_EDGE_ROW_ONE);
		break;
	}
	case 2:{
		return isThisAnEdgeNow(CHANCE_EDGE_ROW_TWO);
		break;
	}
	case 3:{
		return isThisAnEdgeNow(CHANCE_EDGE_ROW_THREE);
		break;
	}
	default:{
		return false; // we should never get here
		break;
	}
	}
}

int Game::edgeCheck(bool xEdge, bool yEdge, int x, int y){
	if(xEdge){ // north or south edge
		if(yEdge){ // east or west edge
			if(x > START_ROOM_X){ // south edge
				if(y > START_ROOM_Y){ // south east edge
					return LocationData::TILE_SOUTH_EAST;
				}
				else{ // south west edge
					return LocationData::TILE_SOUTH_WEST;
				}
			}
			else{ // north edge
				if(y > START_ROOM_Y){ // north east edge
					return LocationData::TILE_NORTH_EAST;
				}
				else{ // north west edge
					return LocationData::TILE_NORTH_WEST;
				}
			}
		}
		else{ // not east or west edge
			if(x > START_ROOM_X){ // south edge
				return LocationData::TILE_SOUTH;
			}
			else{ // north edge
				return LocationData::TILE_NORTH;
			}
		}
	}
	else{ // east or west edge (but no north or south edge)
		if(y > START_ROOM_Y){ // east edge
			return LocationData::TILE_EAST;
		}
		else{ // west edge
			return LocationData::TILE_WEST;
		}
	}
}

void Game::examine(int& old_state){
	(*world)[player->getCurrentFloor()]->getLoc(player->getCurrentX(),player->getCurrentY())->examine(player);
	examineResults(old_state);
}

void Game::examineResults(int& old_state){
	if(player->getCurrentFloor() != player->getPreviousFloor()){ // the player has moved floors
		old_state = state;
		state = STATE_MOVE_FLOOR;
	}
	else if(player->getCurrentFloor() == Player::IS_AT_END_GAME){
		state = STATE_GAME_FINISH;
	}
}

void Game::gameStates(int& old_state, bool& mapPrint, clock_t& startTime){
	switch(state){
	case STATE_EXPLORE:{
		player->setMessageIn(Player::MESSAGE_SLOT_OBJECTIVE,MenuText::MAP_EXPLORE);
		if(isFinalDoorIn){
			state = STATE_FINAL_DOOR;
		}
		break;
	}
	case STATE_FINAL_DOOR:{
		player->setMessageIn(Player::MESSAGE_SLOT_OBJECTIVE,MenuText::MAP_FIND_KEYS);
		if((*world)[player->getCurrentFloor()]->getLoc(finalRoomX,finalRoomY)->getNumOfKeys() == 3){
			//state = STATE_GAME_FINISH;
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
bool Game::getKeyInput(WORD key, int& old_state){
	switch(key)
    {
	case VK_ESCAPE:{
		state = STATE_GAME_FINSH_BAD;
		return false;
		break;
	}
    case VK_LEFT:
	case 0x41: // A // move left
	case VK_NUMPAD4:{ // decrement y
		old_state = state;
		state = STATE_MOVE_LEFT;
		break;
	}
	case VK_UP:
	case 0x57: // W // move up
	case VK_NUMPAD8:{ // decrement x
		old_state = state;
		state = STATE_MOVE_UP;
		break;
	}
	case VK_RIGHT:
	case 0x44: // D // move right
	case VK_NUMPAD6:{ // increment y
		old_state = state;
		state = STATE_MOVE_RIGHT;
		break;
	}
	case VK_DOWN:
	case 0x53: // S // move down
	case VK_NUMPAD2:{ // increment x
		old_state = state;
		state = STATE_MOVE_DOWN;
		break;
	}
	case 0x43:{ // c key // pick up item
		pickUpItem();
		//return true;
		break;
	}
	case 0x45:{ // e key // examine
		examine(old_state);
		//return true; // the map mostlikely changed
		break;
	}
	case 0x48:{ // H key // help
		printHelp();
		//return true;
		break;
	}
	case 0x49: // this was steve as well // i key
	{
		player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,player->getInventory()->displayInventory());
		stringstream str;
		str << MenuText::PLAYER_INVENTORY_PREFIX << player->getInventory()->getNumKeys() << MenuText::PLAYER_INVENTORY_SUFFIX;
		player->setMessageIn(Player::MESSAGE_SLOT_ACTION,str.str());
		//return true;
		break;
	}
	case 0x5A:{ // z key // drop off item
		dropOffItem();
		//return true;
		break;
	}
	default :{
		// we dont move.
		return false;
		break;
	}
    }
	return true;
}

bool Game::hasValidDoor(int nextID){
	switch(state){
	case STATE_MOVE_LEFT:{ // we are entering a door on the right
		switch(nextID){ 
		case LocationData::TILE_EAST:
		case LocationData::TILE_NORTH_EAST:
		case LocationData::TILE_SOUTH_EAST:
		case LocationData::TILE_EAST_WEST:
		case LocationData::TILE_EAST_WEST_SOUTH:
		case LocationData::TILE_EAST_NORTH_SOUTH:
		case LocationData::TILE_EAST_NORTH_WEST:{
			return false; // cannot go through an east wall
			break;
		}
		default:{
			break; // we return at the end
		}
		}
		break;
	}
	case STATE_MOVE_UP:{ // we are entering a door from below
		switch(nextID){
		case LocationData::TILE_SOUTH:
		case LocationData::TILE_SOUTH_EAST:
		case LocationData::TILE_SOUTH_WEST:
		case LocationData::TILE_NORTH_SOUTH:
		case LocationData::TILE_EAST_WEST_SOUTH:
		case LocationData::TILE_EAST_NORTH_SOUTH:
		case LocationData::TILE_NORTH_WEST_SOUTH:{
			return false; // cannot go through a south wall
			break;
		}
		default:{
			break; // we return at the end
		}
		}
		break;
	}
	case STATE_MOVE_RIGHT:{ // we are entering from the left
		switch(nextID){
		case LocationData::TILE_NORTH_WEST:
		case LocationData::TILE_SOUTH_WEST:
		case LocationData::TILE_WEST:
		case LocationData::TILE_EAST_WEST:
		case LocationData::TILE_EAST_WEST_SOUTH:
		case LocationData::TILE_EAST_NORTH_WEST:
		case LocationData::TILE_NORTH_WEST_SOUTH:{
			return false; // cannot go through a west wall
			break;
		}
		default:{
			break; // we return at the end
		}
		}
		break;
	}
	case STATE_MOVE_DOWN:{ // we are entering from the top
		switch(nextID){
		case LocationData::TILE_NORTH:
		case LocationData::TILE_NORTH_EAST:
		case LocationData::TILE_NORTH_WEST:
		case LocationData::TILE_NORTH_SOUTH:
		case LocationData::TILE_EAST_NORTH_SOUTH:
		case LocationData::TILE_EAST_NORTH_WEST:
		case LocationData::TILE_NORTH_WEST_SOUTH:{
			return false; // cannot go through a north wall
			break;
		}
		default:{
			break; // we return at the end
		}
		}
		break;
	}
	default:{
		activeText = "this is completely wrong";
		break; // really we shouldnot be getting here at all
	}
	}
	return true; // this is an acceptable room
}

bool Game::isThisAnEdgeNow(int chance){
	if(getRandomNumber(0,100) < chance){
		return true;
	}
	return false;
}

// @author Andre Allan Ponce
Floor* Game::makeFloor(int id){
	Floor* floor = new Floor(id);
	numberOfFloors++;
	return floor;
}

Location* Game::makeRoom(int id, int x, int y, int flor){
	Location* loc = new Tile(id,x,y,flor); 
	(*world)[flor]->setLoc(loc,x,y);
	setupRoom(loc,id);
	return loc;
}

Location* Game::makeRoomScore(int id, int x, int y, int flor){
	Location* loc = new ExitTile(id,x,y,flor);
	(*world)[flor]->setLoc(loc,x,y);
	setupRoom(loc,id);
	return loc;
}

void Game::makeStairs(Floor* floor, int id, int x, int y, bool isUp){
	setupRoom(floor->createStairs(id,x,y,isUp),id);
}

// @author Andre Allan Ponce
// moves the player on the x and y grid. invalid moving will be fixed probably.
bool Game::movePlayer(int xMove, int yMove){
	if(xMove >= 0 && yMove >= 0 && xMove < Floor::FLOOR_HEIGHT && yMove < Floor::FLOOR_WIDTH){
		if((*world)[player->getCurrentFloor()]->getLoc(xMove,yMove) == 0){
			if(canMoveFrom(player->getCurrentX(),player->getCurrentY())){
				createRandomRoom(xMove,yMove,player->getCurrentFloor());
				player->setCurrentX(xMove);
				player->setCurrentY(yMove);
				return true;
			}
			player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::INVALID_MOVE_WALL);
			return false;
		}
		else if(canMoveFrom(player->getCurrentX(),player->getCurrentY()) != canMoveTo(xMove,yMove)){
			player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::INVALID_MOVE_FAKE_DOOR);
			return false;
		}
		else if(canMoveFrom(player->getCurrentX(),player->getCurrentY()) == true && canMoveTo(xMove,yMove) == true){
			player->setCurrentX(xMove);
			player->setCurrentY(yMove);
			return true;
		}
	}
	player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::INVALID_MOVE_EDGE);
	return false;
}

void Game::movePlayerFloor(){
	int playerX = player->getCurrentX();
	int playerY = player->getCurrentY();
	int previousFloor = player->getPreviousFloor();
	bool up = arePreviousStairsUp(playerX,playerY,previousFloor); // true if we're 
	movePlayerFloorNumber(up);
	if(player->getCurrentFloor() == Player::IS_ON_NEW_FLOOR){ // make a new floor
		player->setCurrentFloor(numberOfFloors);
		int thisFloor = numberOfFloors; // we still need to keep track of the previous floor (playerFloor)
		
		world->push_back(makeFloor(thisFloor)); // auto increments numberOfFloorsgoing up
		makeStairs((*world)[thisFloor],tileIDRandomizer(playerX,playerY),playerX,playerY,!up);

		connectStairs(previousFloor,thisFloor,up);
		player->setPreviousFloor(thisFloor);
		(*world)[thisFloor]->getLoc(playerX,playerY)->visit();
	}
	else{ // move to exisiting floor
		player->setPreviousFloor(player->getCurrentFloor());
	}
	int floorNumber = player->getFloorNumber();
	stringstream str;
	if(floorNumber < 0){
		str << MenuText::FLOOR_NUMBER_PREFIX << MenuText::FLOOR_BASEMENT_PREFIX << abs(floorNumber) << MenuText::FLOOR_NUMBER_SUFFIX;
	}
	else if(floorNumber == 0){
		str << MenuText::FLOOR_GROUND;
	}
	else{
		str <<  MenuText::FLOOR_NUMBER_PREFIX << floorNumber << MenuText::FLOOR_NUMBER_SUFFIX;
	}
	player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,str.str()); 
}

void Game::movePlayerFloorNumber(bool up){
	if(up){
		player->goUpFloor();
	}
	else{
		player->goDownFloor();
	}
}

void Game::pickUpItem(){
	Location* loc = (*world)[player->getCurrentFloor()]->getLoc(player->getCurrentX(),player->getCurrentY());
	if(loc->getNumOfKeys() > Player::INVENTORY_MIN){
		if(player->getInventory()->getNumKeys() < Player::INVENTORY_MAX){
			player->addItem(loc->getItem(Item::ID_KEY));
		}
		else{
			player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::ERROR_NO_INVENTORY_SPACE);
		}
	}
	else{
		player->setMessageIn(Player::MESSAGE_SLOT_INFORMATION,MenuText::ERROR_NO_ROOM_ITEMS);
	}
}

// @author Andre Allan Ponce
// prepping the first two rooms
void Game::preGameInit(){
	createWorld();
	(*world)[START_FLOOR]->setLoc(makeRoom(0,START_ROOM_X,START_ROOM_Y,START_FLOOR),START_ROOM_X,START_ROOM_Y);
	(*world)[START_FLOOR]->set_room_doors(START_ROOM_X,START_ROOM_Y,true); //the first room should have all open doors
	//player = new Player(Player::PLAYER_SYMBOL,START_ROOM_X,START_ROOM_Y,START_FLOOR);
	player->setCurrentFloor(START_FLOOR);
	player->setPreviousFloor(START_FLOOR);
	player->setCurrentX(START_ROOM_X);
	player->setCurrentY(START_ROOM_Y);
	player->setSymbol(Player::PLAYER_SYMBOL);
	player->createInventory();
	state = STATE_EXPLORE;
}

void Game::prepareMovePlayer(){
	switch(state){
	case STATE_MOVE_LEFT:{ // decrement y
		movePlayer(player->getCurrentX(),player->getCurrentY()-1);
		break;
	}
	case STATE_MOVE_UP:{ // decrement x
		movePlayer(player->getCurrentX()-1,player->getCurrentY());
		break;
	}
	case STATE_MOVE_RIGHT:{ // increment y
		movePlayer(player->getCurrentX(),player->getCurrentY()+1);
		break;
	}
	case STATE_MOVE_DOWN:{ // increment x
		movePlayer(player->getCurrentX()+1,player->getCurrentY());
		break;
	}
	default:{
		// we should never be going here because this method is only run when we have grid movement
		break;
	}
	}
	(*world)[player->getCurrentFloor()]->getLoc(player->getCurrentX(),player->getCurrentY())->action(player);
}

void Game::setupDoors(Location* loc, int id){
	if(id != LocationData::TILE_NORTH && id != LocationData::TILE_NORTH_EAST && id != LocationData::TILE_NORTH_WEST && id != LocationData::TILE_EAST_NORTH_SOUTH && id != LocationData::TILE_EAST_NORTH_WEST && id != LocationData::TILE_NORTH_SOUTH && id != LocationData::TILE_NORTH_WEST_SOUTH){
		loc->set_north_door(true);
	}
	if(id != LocationData::TILE_EAST && id != LocationData::TILE_NORTH_EAST && id != LocationData::TILE_SOUTH_EAST && id != LocationData::TILE_EAST_NORTH_SOUTH && id != LocationData::TILE_EAST_NORTH_WEST && id != LocationData::TILE_EAST_WEST && id != LocationData::TILE_EAST_WEST_SOUTH){
		loc->set_east_door(true);
	}
	if(id != LocationData::TILE_SOUTH && id != LocationData::TILE_SOUTH_EAST && id != LocationData::TILE_SOUTH_WEST && id != LocationData::TILE_EAST_NORTH_SOUTH && id != LocationData::TILE_EAST_WEST_SOUTH && id != LocationData::TILE_NORTH_SOUTH && id != LocationData::TILE_NORTH_WEST_SOUTH){
		loc->set_south_door(true);
	}
	if(id != LocationData::TILE_WEST && id != LocationData::TILE_SOUTH_WEST && id != LocationData::TILE_NORTH_WEST && id != LocationData::TILE_EAST_NORTH_WEST && id != LocationData::TILE_EAST_WEST && id != LocationData::TILE_EAST_WEST_SOUTH && id != LocationData::TILE_NORTH_WEST_SOUTH){
		loc->set_west_door(true);
	}
}

void Game::setupRoom(Location* loc, int id){
	loc->createNewArray(locations.retrieveRoom(id));
	setupDoors(loc,id);
	//(*world)[loc->getFloorID()]->syncDoors(loc->getCoordinateX(),loc->getCoordinateY());
}

int Game::tileIDRandomizer(int x, int y){
	int xDistance = distanceFromEdge(x);
	int yDistance = distanceFromEdge(y);
	if(xDistance <= 3 || yDistance <= 3){
		return edgeCheck(edgeChanceMaker(xDistance),edgeChanceMaker(yDistance),x,y);
	}
	return getRandomNumber(0,locations.getSize());
}

// ==== public methods ====

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
	std::cout << (*world)[player->getCurrentFloor()]->getNewMap(player->getCurrentX(),player->getCurrentY(),player->getSymbol()) << MenuText::MAP_EDGE_BOTTOM << "\n";
	std::cout << player->getMessages(); // more efficient
	//std::cout << activeText << "\n";
	//std::cout << modeText << "\n";
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
	std::cout << MenuText::MENU_HELP_CURRENT_PLAYER << (*player) << "\n";
	std::cout << MenuText::MENU_HELP;
	system("pause");
}

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

std::vector<Player*>* Game::readInSaveFile(std::string fileName){
	std::ifstream inFile;
	inFile.open(fileName.c_str());
	if(!inFile.good()){
		throw MenuText::ERROR_FILE_NAME;
	}
	int numberOfPlayers;
	inFile >> numberOfPlayers;
	std::vector<Player*>* players = new std::vector<Player*>(numberOfPlayers);
	inFile.ignore(10, '\n');
	int index = 0;
	while(!inFile.eof()){
		(*players)[index] = new Player();
		inFile >> (*(*players)[index]);
		(*players)[index]->setIndex(index);
		inFile.ignore(10, '\n');
		index++;
	}
	inFile.close();
	return players;
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
			player->setMessageIn(Player::MESSAGE_SLOT_OBJECTIVE,MenuText::MAP_EXPLORE);
			printHelp();
			printGame();
			old_state = STATE_PRE_GAME;
			break;
		}
		case STATE_GAME_FINISH:{
			player->clearMessages();
			player->setMessageIn(Player::MESSAGE_SLOT_OBJECTIVE,MenuText::GAME_WINNER);
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
		case STATE_MOVE_UP:
		case STATE_MOVE_RIGHT:
		case STATE_MOVE_DOWN:
		case STATE_MOVE_LEFT:{
			prepareMovePlayer();
			state = old_state;
			break;
		}
		case STATE_MOVE_FLOOR:{
			movePlayerFloor();
			state = old_state;
			break;
		}
		default:{
			gameStates(old_state,updateMap,startTime);
			if(updateMap){
				//printGamePartial();
				//std::cout << "even\n";
				printGame();
				updateMap = false;
			}
			do ReadConsoleInput( hInput, &irInput, 1, &InputsRead );
			while ((irInput.EventType != KEY_EVENT) || irInput.Event.KeyEvent.bKeyDown);
			//ReadConsoleInput(hInput, &irInput, 1, &InputsRead); 
			player->clearMessages();
			startTime = clock();
			//Location* thisRoom = world[player][currY];
			updateMap = getKeyInput(irInput.Event.KeyEvent.wVirtualKeyCode,old_state);
			break;
		}
		}
	}
}

void Game::savePlayersFile(std::vector<Player*>* players, std::string fileName){
	std::ofstream outFile;
	outFile.open(fileName.c_str());
	if(!outFile.good()){
		throw MenuText::ERROR_FILE_NAME;
	}
	int end = players->size();
	outFile << end << "\n";
	for(int i = 0; i < end; i++){
		outFile << (*(*players)[i]);
		if(i < end-1){
			outFile << "\n";
		}
	}
	outFile.close();
}

void Game::setPlayer(Player& p){
	player = &p;
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

