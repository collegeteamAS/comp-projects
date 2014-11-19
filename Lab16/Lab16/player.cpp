/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Player class
*/

#include <string>
#include "player.h"


// @author Andre Allan Ponce
/*//
Player::Player() : 
	symbol(sym), // d stands for debug
	//xBoard(-1), 
	//yBoard(-1),
	//inventory(0),
	//keys(0),
	curr_floor(-1){
	// constructors should be empty, yo
}//*/

// @author Andre Allan Ponce
Player::Player(char sym) : 
	symbol(sym)
	//xBoard(-1), 
	//yBoard(-1),
	//inventory(0),
	//keys(0),
	//curr_floor(-1){
	// constructors should be empty, yo
{

}

/*//
Player::~Player(){
	deleteInventory();
}//*/
/*//
void Player::addItem(Node* item){
	inventory->add_node(item);
	keys++;
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
//*/
// @author Andre Allan Ponce
char Player::getSymbol(){
	return symbol;
}
/*//
Node* Player::removeItem(int id){
	keys--;
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

void Player::setName(std::string nam){
	name = nam;
}
//*/