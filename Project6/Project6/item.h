//steve suh

#ifndef _ITEM_H_INCLUDED_
#define _ITEM_H_INCLUDED_

class Item {
private:

	char symbol;//symbol of the item on the printed screen
	int id;

public:

	Item();
	void setID(int idNum); 
	int getID();

	void setSymbol(char sym);
	char getSymbol();
};

#endif