/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Player class
*/

#include <string>
//#include <sstream> // converting ints to strings takes some work
#include "player.h"

/* THESE INCLUDE A NAME STRING (we'll see if we still need name string)
// @author Andre Allan Ponce
Player::Player() : name("debug"), symbol('d'), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1){
	// constructors should be empty, yo
}

// @author Andre Allan Ponce
Player::Player(std::string n, char sym) : name(n), symbol(sym), xBoard(-1), yBoard(-1), xRoom(-1), yRoom(-1){
	// constructors should be empty, yo
}
//*/

// @author Andre Allan Ponce
//Steve Suh
Player::Player() : 
	symbol('d'), // d stands for debug
	xBoard(-1), 
	yBoard(-1), 
	xRoom(-1), 
	yRoom(-1){
	// constructors should be empty, yo
}

// @author Andre Allan Ponce
Player::Player(char sym) : 
	symbol(sym), 
	xBoard(-1), 
	yBoard(-1), 
	xRoom(-1), 
	yRoom(-1){ ;
	// constructors should be empty, yo
}

//Steve Suh
int Player::detectItemID() // returns id of the item
{
	/*
		*world[currX][currY][
			return i.getItemID();
	*/
}


// @author Andre Allan Ponce
int Player::getBoardLocX(){
	return xBoard;
}

// @author Andre Allan Ponce
int Player::getBoardLocY(){
	return yBoard;
}

// @author Andre Allan Ponce
int Player::getRoomLocX(){
	return xRoom;
}

// @author Andre Allan Ponce
int Player::getRoomLocY(){
	return yRoom;
}

/*
// @author Andre Allan Ponce
std::string Player::getName(){
	return name;
}//*/

// @author Andre Allan Ponce
char Player::getSymbol(){
	return symbol;
}

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

/*
// @author Andre Allan Ponce
std::string Player::print(){
	return "Name: "+name+"\n";
		//"Age: "+temp.str()+"\n";
}//*/

// @author Andre Allan Ponce
void Player::setBoardLocX(int x){
	xBoard = x;
}

// @author Andre Allan Ponce
void Player::setBoardLocY(int y){
	yBoard = y;
}

// @author Andre Allan Ponce
void Player::setRoomLocX(int x){
	xRoom = x;
}

// @author Andre Allan Ponce
void Player::setRoomLocY(int y){
	yRoom = y;
}

/*
// @author Andre Allan Ponce
void Player::setName(std::string n){
	name = n;
}//*/
