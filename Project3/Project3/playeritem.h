/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Item class, for the player's items
*/
#ifndef _PLAYERITEM_H_INCLUDED_
#define _PLAYERITEM_H_INCLUDED_

class PlayerItem : public Item{
protected:
	int id;

public:
	PlayerItem();
	PlayerItem(std::string n, int idNumber);

	virtual void action() = 0;

	int getID();

	void setID(int idNumber);
};
#endif