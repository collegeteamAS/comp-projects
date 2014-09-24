/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	room items, like furniture and stuff.
*/

#include <string>
#include "item.h"
#include "roomitem.h"

// @author Andre Allan Ponce
RoomItem::RoomItem() : Item(){
	// empty
}

// @author Andre Allan Ponce
RoomItem::RoomItem(std::string n) : Item(n){
	// empty
}