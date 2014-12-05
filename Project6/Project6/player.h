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

	2014-12-04
	+ added operators for extracting and insertion
	+ added variable and methods for player score
	+ added variable and methods for player name
	+ added variable and methods for player's index value (for saving)
*/
#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include <string>

class LinkedList;
class Node;

class Player{
private:
	std::string name; // we might have multiple players

	char symbol;

	// location on Location Board
	int xBoard;
	int yBoard;

	// player score
	int score;

	// player index
	int index;

	// current floor
	int floorCurrent;

	// the previous floor
	int floorPrevious;

	int floorNumber; // what floor the player is on relative to ground (START_FLOOR)

	// players items
	LinkedList* inventory;

	// the player now contains MESSAGE_SLOTS number of messages
	static const int MESSAGE_SLOTS = 4;

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
		MESSAGE_SLOT_SCORE = 3,

		// Player floor id 
		IS_AT_END_GAME = -2,
		IS_ON_NEW_FLOOR = -1
	};

	Player();
	Player(char sym);
	Player(char sym, int xLocation, int yLocation, int floorLocation);
	~Player();

	void addItem(Node* item);
	void addToScore(int s); 
	void clearMessages();
	void createInventory();
	void deleteInventory();

	int getCurrentFloor();
	int getCurrentX();
	int getCurrentY();
	void goDownFloor();
	int getFloorNumber();
	int getIndex();
	LinkedList* getInventory();
	std::string getMessageIn(int slot); // does NOT return newline
	std::string getMessages(); // RETURNS newline
	std::string getName();
	int getPreviousFloor();
	int getScore();
	char getSymbol();
	void goUpFloor();

	// for saving
	friend std::istream& operator>>(std::istream& in, Player& p);
	friend std::ostream& operator<<(std::ostream& out, Player& p);

	void removeFromScore(int s);
	Node* removeItem(int id);

	void setCurrentFloor(int floor);
	void setCurrentX(int x);
	void setCurrentY(int y);
	void setFloorNumber(int floor);
	void setIndex(int i);
	bool setMessageIn(int slot, std::string line); // NEVER set message with newline
	// @returns true if message set was successful, false if out of bounds
	void setName(std::string n);
	void setPreviousFloor(int floor);
	void setScore(int s);
	void setSymbol(char sym);
	
	void updateFloor();
};

#endif
