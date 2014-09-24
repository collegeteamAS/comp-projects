/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	room items, like furniture and stuff.
*/
#ifndef _ROOMITEM_H_INCLUDED_
#define _ROOMITEM_H_INCLUDED_

class RoomItem : public Item{
public:
	RoomItem();
	RoomItem(std::string n);

	virtual void action() = 0;
};
#endif