/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Header for Player class
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

	std::string* messages;

public:
	enum Constants{
		INVENTORY_MAX = 3,
		INVENTORY_MIN = 0
	};

	Player();
	Player(char sym);
	~Player();

	void addItem(Node* item);
	void createInventory();
	void deleteInventory();

	int getBoardLocX();
	int getBoardLocY();
	int get_current_floor();
	LinkedList* getInventory();
	char getSymbol();

	Node* removeItem(int id);

	void setBoardLocX(int x);
	void setBoardLocY(int y);
	void set_current_floor(int floor);

};

#endif
