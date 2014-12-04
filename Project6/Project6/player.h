/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Header for Player class

	2014-12-02
	+ added string container for messages
	+ added methods for clearing messages, getting messages, and setting messages

	2014-12-03
	+ added constructor for creating Player with known board locations 
	+ added variable and methods for storing and retreiving the player's previous floor
	+ added variable and get method to keep track of this floor relative to ground
	= renamed curr_floor to floorCurrent for clairty
	= renamed approparite current floor methods to camelCase versions for clarity
*/
#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include <string>

class LinkedList;
class Node;

class Player{
private:
	char symbol;

	// location on Location Board
	int xBoard;
	int yBoard;

	// current floor
	int floorCurrent;

	// the previous floor
	int floorPrevious;

	int floorNumber; // what floor the player is on relative to ground (START_FLOOR)

	// players items
	LinkedList* inventory;

	// the player now contains MESSAGE_SLOTS number of messages
	static const int MESSAGE_SLOTS = 3;

	// contains message for the game to display
	std::string messages[MESSAGE_SLOTS];


public:
	enum Constants{
		PLAYER_SYMBOL = 'O',

		INVENTORY_MAX = 3,
		INVENTORY_MIN = 0,

		// message slots
		MESSAGE_SLOT_OBJECTIVE = 0,
		MESSAGE_SLOT_ACTION = 1,
		MESSAGE_SLOT_INFORMATION = 2,

		// Player floor id 
		IS_AT_END_GAME = -2,
		IS_ON_NEW_FLOOR = -1
	};

	Player();
	Player(char sym);
	Player(char sym, int xLocation, int yLocation, int floorLocation);
	~Player();

	void addItem(Node* item);
	void clearMessages();
	void createInventory();
	void deleteInventory();

	int getCurrentFloor();
	int getCurrentX();
	int getCurrentY();
	void goDownFloor();
	int getFloorNumber();
	LinkedList* getInventory();
	std::string getMessageIn(int slot); // does NOT return newline
	std::string getMessages(); // RETURNS newline
	int getPreviousFloor();
	char getSymbol();
	void goUpFloor();

	Node* removeItem(int id);

	void setCurrentFloor(int floor);
	void setCurrentX(int x);
	void setCurrentY(int y);
	void setFloorNumber(int floor);
	bool setMessageIn(int slot, std::string line); // NEVER set message with newline
	// @returns true if message set was successful, false if out of bounds
	void setPreviousFloor(int floor);
	
	void updateFloor();
};

#endif
