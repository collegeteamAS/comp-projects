/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Item class, for all the items
*/

#include <string>
#include "item.h"

// @author Andre Allan Ponce
Item::Item() : name("debug"){
	// constructors should be empty, yo
}

// @author Andre Allan Ponce
Item::Item(std::string n) : name(n){
	// constructors should be empty, yo
}

// @author Andre Allan Ponce
std::string Item::getItemName(){
	return name;
}

// @author Andre Allan Ponce
void Item::setItemName(std::string n){
	name = n;
}