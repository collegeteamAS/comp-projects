/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Item class, for all the items
*/
#ifndef _ITEM_H_INCLUDED_
<<<<<<< HEAD
#define _ITEM_H_INCLUDED


class Item
{
	protected:
		// location on Location Board
		int xBoard;
		int yBoard;

		// location in room
		int xRoom;
		int yRoom;
	public:
		char symbol;
		std::string description;

		Item();
		Item(char sym);

		virtual void action();
		char getSymbol();
		int getBoardLocX();
		int getBoardLocY();
		int getItemLocX();
		int getItemLocY();
=======

#define _ITEM_H_INCLUDED_


class Item{
protected:
	// location on Location Board
	int xBoard;
	int yBoard;

	// location in room
	int xRoom;
	int yRoom;


	char symbol;
	bool keyAcheived;
	int id;
	std::string descript;
public:
	

	Item();
	Item(char sym, int idNum);

	virtual void action();

	char getSymbol();
	int getID();
	std::string getDescription();
	int getBoardLocX();
	int getBoardLocY();
	int getItemLocX();
	int getItemLocY();

	void setDescription(std::string desc);

>>>>>>> e692805bc743cdf709b3569e29a559e39528d45b
};
#endif
