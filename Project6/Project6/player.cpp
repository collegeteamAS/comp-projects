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

Player::~Player(){
	deleteInventory();
}

// ==== public methods ====

void Player::addItem(Node* item){
	inventory->add_node(item);
}

void Player::clearMessages(){
	for(int i = 0; i < MESSAGE_SLOTS; i++){
		messages[i] = "";
	}
}

void Player::createInventory(){
	inventory = new LinkedList();
}

void Player::deleteInventory(){
	if(inventory != 0){
		delete inventory;
	}
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

std::string Player::getMessageIn(int slot){
	if(slot < MESSAGE_SLOTS && slot >= 0){
		return messages[slot];
	}
	else{
		return " bad mesage"; // replace with MenuText variant
	}
}

std::string Player::getMessages(){
	std::string message = "";
	for(int i = 0; i < MESSAGE_SLOTS; i++){
		message = message + messages[i] + "\n";
	}
	return message;
}

// @author Andre Allan Ponce
char Player::getSymbol(){
	return symbol;
}

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

bool Player::setMessageIn(int slot, std::string line){
	if(slot < MESSAGE_SLOTS && slot >= 0){
		messages[slot] = line;
		return true;
	}
	return false;
}