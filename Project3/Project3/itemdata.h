/*
Steve Suh
h_suh@u.pacific.edu
*/
#ifndef _ITEMDATA_H_INCLUDED_
#define _ITEMDATA_H_INCLUDED_

#include <unordered_map>

class ItemData{
private:
	std::unordered_map<int,char**> data;

	// private methods
	std::string name;
	std::string description;
public:
	enum Constants{
		// RoomItem IDs
		ROOMITEM_JUNK = 0,
		ROOMITEM_VASE = 1,
		ROOMITEM_TABLE = 2,
		ROOMITEM_CHAIR = 3,
		ROOMITEM_LAMP = 4,
		ROOMITEM_BED = 5,
		ROOMITEM_CANDLE = 6,
		ROOMITEM_DISH = 7,
		ROOMITEM_DUST = 8,
		ROOMITEM_FORK = 9,
		ROOMITEM_TOILET = 10,
		ROOMITEM_BATHTUB = 11,
		ROOMITEM_MIRROR = 12,
		ROOMITEM_BLOOD = 13,
		ROOMITEM_CD = 14,

		// player item IDs
		PLAYERITEM_KEY = 0,

	};

	Item retrieveItem(int id);


	std::string getItemName();
	void setItemName(std::string n);
};

#endif