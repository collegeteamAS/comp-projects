/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Player class
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "player.h"
#include "linkedList.h"
#include "node.h"
#include "menutext.h"


// @author Andre Allan Ponce
Player::Player() : 
	symbol('d'), // d stands for debug
	xBoard(-1), 
	yBoard(-1),
	name(""),
	score(0),
	index(-1),
	inventory(0),
	floorPrevious(-1),
	floorNumber(0),
	floorCurrent(-1){
	clearMessages();
}

// @author Andre Allan Ponce
Player::Player(char sym) : 
	symbol(sym), 
	xBoard(-1), 
	yBoard(-1),
	name(""),
	score(0),
	index(-1),
	inventory(0),
	floorPrevious(-1),
	floorNumber(0),
	floorCurrent(-1){
	clearMessages();
}

Player::Player(char sym, int xLocation, int yLocation, int floorLocation) :
	symbol(sym),
	xBoard(xLocation),
	yBoard(yLocation),
	name(""),
	score(0),
	index(-1),
	inventory(0),
	floorPrevious(floorLocation),
	floorNumber(floorLocation),
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

void Player::addToScore(int s){
	score += s;
}

void Player::clearMessages(){
	for(int i = 0; i < MESSAGE_SLOTS; i++){
		messages[i] = MenuText::PLAYER_MESSAGE_BLANK;
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

void Player::goDownFloor(){
	--floorNumber;
}

int Player::getFloorNumber(){
	return floorNumber;
}

int Player::getIndex(){
	return index;
}

LinkedList* Player::getInventory(){
	return inventory;
}

std::string Player::getMessageIn(int slot){
	if(slot < MESSAGE_SLOTS && slot >= 0){
		return messages[slot];
	}
	else{
		return MenuText::PLAYER_MESSAGE_INVALID_SLOT; // replace with MenuText variant
	}
}

std::string Player::getMessages(){
	std::string message = "";
	stringstream str;
	str << MenuText::PLAYER_SCORE_PREFIX << getScore() << MenuText::PLAYER_SCORE_SUFFIX;
	setMessageIn(MESSAGE_SLOT_SCORE,str.str());
	for(int i = 0; i < MESSAGE_SLOTS; i++){
		message = message + messages[i] + "\n";
	}
	return message;
}

std::string Player::getName(){
	return name;
}

int Player::getPreviousFloor(){
	return floorPrevious;
}

int Player::getScore(){
	return score;
}

// @author Andre Allan Ponce
char Player::getSymbol(){
	return symbol;
}

void Player::goUpFloor(){
	++floorNumber;
}

std::istream& operator>>(std::istream& in, Player& p){
	in >> p.name >> p.score;
	return in;
}

std::ostream& operator<<(std::ostream& out, Player& p){
	out << p.name << " " << p.score;
	return out;
}

void Player::removeFromScore(int s){
	score -= s;
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

void Player::setFloorNumber(int floor){
	floorNumber = floor;
}

void Player::setIndex(int i){
	index = i;
}

bool Player::setMessageIn(int slot, std::string line){
	if(slot < MESSAGE_SLOTS && slot >= 0){
		messages[slot] = line;
		return true;
	}
	return false;
}

void Player::setName(std::string n){
	name = n;
}

void Player::setPreviousFloor(int floor){
	floorPrevious = floor;
}

void Player::setScore(int s){
	score = s;
}

void Player::setSymbol(char sym){
	symbol = sym;
}

void Player::updateFloor(){
	floorPrevious = floorCurrent;
}