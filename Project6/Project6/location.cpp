
/*
Andre Allan Ponce
a_ponce1@u.pacific.edu
Steve Suh
h_suh@u.pacific.edu
*/


#include <string>
#include "location.h"
#include "linkedList.h"
#include "tile.h"


// @author Andre Allan Ponce
Location::Location() : 
	x(-1), 
	y(-1),
	id(-1), 
	items(0),
	endGame(false),
	has_east_door(false),
	has_north_door(false),
	has_south_door(false),
	has_west_door(false),
	roomLayout(0){
	items = new LinkedList();
}

// @author Andre Allan Ponce
Location::Location(int idNum, int xCoord, int yCoord) : 
	x(xCoord), 
	y(yCoord),
	id(idNum),
	items(0),
	endGame(false),
	has_east_door(false),
	has_north_door(false),
	has_south_door(false),
	has_west_door(false),
	roomLayout(0){
	items = new LinkedList();
}

Location::~Location(){
	deleteItems();
	deleteLayout();
}

void Location::addItem(Node* n){
	items->add_node(n);
}

void Location::deleteItems(){
	if(items != 0){
		delete items;
	}
}

void Location::deleteLayout(){
	if(roomLayout != 0){
		for(int i = 0; i < Tile::TILE_HEIGHT; i++){
			if(roomLayout[i] != 0){
				delete [] roomLayout[i];
			}
		}
		delete [] roomLayout;
	}
}

bool Location::get_east_door(){
	return has_east_door;
}

bool Location::get_north_door(){
	return has_north_door;
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

bool Location::get_south_door(){
	return has_south_door;
}

bool Location::get_west_door(){
	return has_west_door;
}

bool Location::isFinalRoom(){
	return endGame;
}

void Location::set_east_door(bool value){
	has_east_door = value;
}

void Location::setFinalRoom(bool value){
	endGame = value;
}

void Location::set_north_door(bool value){
	has_north_door = value;
}

// @author Andre Allan Ponce
void Location::setRoomID(int idNum){
	id = idNum;
}

void Location::set_south_door(bool value){
	has_south_door = value;
}

void Location::set_west_door(bool value){
	has_west_door = value;
}
