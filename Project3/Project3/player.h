/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Header for Player class
	Steve Suh
	h_suh@u.pacific.edu
*/
#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_
#include <array>
class Player{
private:
	//std::string name;
	static const int INVENTORY_MAX;
	char symbol;

	// location on Location Board
	int xBoard;
	int yBoard;

	// location in room
	int xRoom;
	int yRoom;

public:

	Player();
	//Player(std::string n, char sym);
	Player(char sym);

<<<<<<< HEAD
	//int detectItemID();
=======
	
	int detectItemID();
>>>>>>> 82e96c42889245432fdc5395350a0c76a2f27fc2
	int getBoardLocX();
	int getBoardLocY();
	int getRoomLocX();
	int getRoomLocY();
	//std::string getName();
	char getSymbol();

	void moveDown();
	void moveLeft();
	void moveRight();
	void moveUp();

	// std::string print(); // return string, so we dont have include iostream everywhere

	void setBoardLocX(int x);
	void setBoardLocY(int y);
	void setRoomLocX(int x);
	void setRoomLocY(int y);
	//void setName(std::string n);
};

#endif