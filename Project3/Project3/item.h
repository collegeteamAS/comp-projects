/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Item class, for all the items
*/
#ifndef _ITEM_H_INCLUDED_
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
		bool keyAcheived;
		std::string description;

		Item();
		Item(char sym);

		virtual void action();
		char getSymbol();
		int getBoardLocX();
		int getBoardLocY();
		int getItemLocX();
		int getItemLocY();
};
#endif
