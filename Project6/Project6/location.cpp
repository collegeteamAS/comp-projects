
/*
Andre Allan Ponce
a_ponce1@u.pacific.edu
Steve Suh
h_suh@u.pacific.edu
*/


//#include <string>
#include "location.h"
#include "linkedList.h"


// @author Andre Allan Ponce
Location::Location() : 
	x(-1), 
	y(-1),
	id(-1),
	floorID(-1),
	symbol('d'),
	items(0),
	endGame(false),
	visited(false),
	has_east_door(false),
	has_north_door(false),
	has_south_door(false),
	has_west_door(false),
	roomLayout(0){
	items = new LinkedList();
}

// @author Andre Allan Ponce
Location::Location(int idNum, int xCoord, int yCoord, int floor, char sym) : 
	x(xCoord), 
	y(yCoord),
	id(idNum),
	floorID(floor),
	symbol(sym),
	items(0),
	endGame(false),
	visited(false),
	has_east_door(false),
	has_north_door(false),
	has_south_door(false),
	has_west_door(false),
	roomLayout(0){
	items = new LinkedList();
}

Location::~Location(){
	deleteItems();
}

// ==== private methods ====

void Location::deleteItems(){
	if(items != 0){
		delete items;
	}
}

// ==== public methods ====

void Location::addItem(Node* n){
	items->add_node(n);
}

bool Location::get_east_door(){
	return has_east_door;
}

bool Location::get_north_door(){
	return has_north_door;
}

bool Location::get_south_door(){
	return has_south_door;
}

bool Location::get_west_door(){
	return has_west_door;
}

int Location::getCoordinateX(){
	return x;
}

int Location::getCoordinateY(){
	return y;
}

int Location::getFloorID(){
	return floorID;
}

Node* Location::getItem(int id){
	return items->remove_node(id);
}

int Location::getNumOfKeys(){
	return items->getNumKeys();
}

// @author Andre Allan Ponce
int Location::getRoomID(){
	return id;
}

char Location::getSymbol(){
	return symbol;
}

bool Location::isFinalRoom(){
	return endGame;
}

void Location::setFinalRoom(bool value){
	endGame = value;
}

// @author Andre Allan Ponce
void Location::setRoomID(int idNum){
	id = idNum;
}

void Location::visit(){
	visited = true;
}

void Location::set_east_door(bool value){
	has_east_door = value;
}

void Location::set_north_door(bool value){
	has_north_door = value;
}

void Location::set_south_door(bool value){
	has_south_door = value;
}

void Location::set_west_door(bool value){
	has_west_door = value;
}
