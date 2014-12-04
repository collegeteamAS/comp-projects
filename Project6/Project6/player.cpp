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
	floorPrevious(-1),
	floorCurrent(-1){
	clearMessages();
}

// @author Andre Allan Ponce
Player::Player(char sym) : 
	symbol(sym), 
	xBoard(-1), 
	yBoard(-1),
	inventory(0),
	floorPrevious(-1),
	floorCurrent(-1){
	clearMessages();
}

Player::Player(char sym, int xLocation, int yLocation, int floorLocation) :
	symbol(sym),
	xBoard(xLocation),
	yBoard(yLocation),
	inventory(0),
	floorPrevious(floorLocation),
	floorCurrent(floorLocation){
	clearMessages();
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

int Player::getCurrentFloor(){
	return floorCurrent;
}

int Player::getCurrentX(){
	return xBoard;
}

int Player::getCurrentY(){
	return yBoard;
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

int Player::getPreviousFloor(){
	return floorPrevious;
}

// @author Andre Allan Ponce
char Player::getSymbol(){
	return symbol;
}

Node* Player::removeItem(int id){
	return inventory->remove_node(id);
}

void Player::setCurrentFloor(int floor){
	floorCurrent = floor;
}

void Player::setCurrentX(int x){
	xBoard = x;
}

void Player::setCurrentY(int y){
	yBoard = y;
}

bool Player::setMessageIn(int slot, std::string line){
	if(slot < MESSAGE_SLOTS && slot >= 0){
		messages[slot] = line;
		return true;
	}
	return false;
}

void Player::setPreviousFloor(int floor){
	floorPrevious = floor;
}

void Player::updateFloor(){
	floorPrevious = floorCurrent;
}