/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Header for Player class

	2014-12-02
	+added string container for messages
	+added methods for clearing messages, getting messages, and setting messages
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
	int curr_floor;

	// players items
	LinkedList* inventory;

	// the player now contains MESSAGE_SLOTS number of messages
	static const int MESSAGE_SLOTS = 3;

	// contains message for the game to display
	std::string messages[MESSAGE_SLOTS];


public:
	enum Constants{
		INVENTORY_MAX = 3,
		INVENTORY_MIN = 0,
	};

	Player();
	Player(char sym);
	~Player();

	void addItem(Node* item);
	void clearMessages();
	void createInventory();
	void deleteInventory();

	int getBoardLocX();
	int getBoardLocY();
	int get_current_floor();
	LinkedList* getInventory();
	std::string getMessageIn(int slot); // does NOT return newline
	std::string getMessages(); // RETURNS newline
	char getSymbol();

	Node* removeItem(int id);

	void setBoardLocX(int x);
	void setBoardLocY(int y);
	void set_current_floor(int floor);
	bool setMessageIn(int slot, std::string line); // NEVER set message with newline
	// @returns true if message set was successful, false if out of bounds

};

#endif
