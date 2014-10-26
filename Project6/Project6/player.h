/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Header for Player class
*/
#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

class Player{
private:
	//std::string name;
	static const int INVENTORY_MAX;
	char symbol;

	// location on Location Board
	int xBoard;
	int yBoard;

	// current floor
	int curr_floor;

	// location in room
	// not need for now
	//int xRoom;
	//int yRoom;

public:
	Player();
	//Player(std::string n, char sym);
	Player(char sym);


	int getBoardLocX();
	int getBoardLocY();
	int get_current_floor();
	//int getRoomLocX();
	//int getRoomLocY();
	//std::string getName();
	char getSymbol();

	/* we dont really need this, since moving up and down is a board change
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveUp();
	//*/
	// std::string print(); // return string, so we dont have include iostream everywhere

	void setBoardLocX(int x);
	void setBoardLocY(int y);
	void set_current_floor(int floor);
	//void setRoomLocX(int x);
	//void setRoomLocY(int y);
	//void setName(std::string n);
};

#endif
