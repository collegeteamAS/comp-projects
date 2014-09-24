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

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> d4dfddad49204a11b01280c1c51e60bb6bfb2c56
		Item();
		Item(char sym);

		virtual void action();
		char getSymbol();
		int getBoardLocX();
		int getBoardLocY();
		int getItemLocX();
		int getItemLocY();
<<<<<<< HEAD
>>>>>>> 82e96c42889245432fdc5395350a0c76a2f27fc2
=======
>>>>>>> d4dfddad49204a11b01280c1c51e60bb6bfb2c56
};
#endif
