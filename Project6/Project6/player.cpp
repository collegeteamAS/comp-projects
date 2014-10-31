/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Player class
*/

#include <string>
#include "player.h"
#include "linkedList.h"
#include "node.h"


// @author Andre Allan Ponce
Player::Player() : 
	symbol('d'), // d stands for debug
	xBoard(-1), 
	yBoard(-1),
	inventory(0),
	curr_floor(-1){
	// constructors should be empty, yo
}

// @author Andre Allan Ponce
Player::Player(char sym) : 
	symbol(sym), 
	xBoard(-1), 
	yBoard(-1),
	inventory(0),
	curr_floor(-1){
	// constructors should be empty, yo
}

void Player::addItem(Node* item){
	inventory->add_node(item);
}

void Player::createInventory(){
	inventory = new LinkedList();
}

// @author Andre Allan Ponce
int Player::getBoardLocX(){
	return xBoard;
}

// @author Andre Allan Ponce
int Player::getBoardLocY(){
	return yBoard;
}

int Player::get_current_floor(){
	return curr_floor;
}

LinkedList* Player::getInventory(){
	return inventory;
}

/*
// @author Andre Allan Ponce
int Player::getRoomLocX(){
	return xRoom;
}

// @author Andre Allan Ponce
int Player::getRoomLocY(){
	return yRoom;
}
//*/


// @author Andre Allan Ponce
char Player::getSymbol(){
	return symbol;
}

/*
// @author Andre Allan Ponce
void Player::moveDown(){
	xRoom++;
}

// @author Andre Allan Ponce
void Player::moveLeft(){
	yRoom--;
}

// @author Andre Allan Ponce
void Player::moveRight(){
	yRoom++;
}

// @author Andre Allan Ponce
void Player::moveUp(){
	xRoom--;
}
//*/

Node* Player::removeItem(int id){
	return inventory->remove_node(id);
}

// @author Andre Allan Ponce
void Player::setBoardLocX(int x){
	xBoard = x;
}

// @author Andre Allan Ponce
void Player::setBoardLocY(int y){
	yBoard = y;
}

void Player::set_current_floor(int floor){
	curr_floor = floor;
}

/*
// @author Andre Allan Ponce
void Player::setRoomLocX(int x){
	xRoom = x;
}

// @author Andre Allan Ponce
void Player::setRoomLocY(int y){
	yRoom = y;
}//*/
