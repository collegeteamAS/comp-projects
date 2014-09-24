
//#include <unordered_map>
#include "itemdata.h"

ItemData::ItemData() :
	size(-1),
	data(0){

}

ItemData::ItemData(int s) : 
	size(s),
	data(0){

}

// @author Andre Allan Ponce
void ItemData::createItemEntry(int id, std::string n, std::string d){
	std::string* strs = new std::string[2];
	strs[0] = n;
	strs[1] = d;
	data.emplace(id,strs);
}

// @author Andre Allan Ponce
std::string ItemData::getItemDesc(int id){
	return data.at(id)[ITEM_DESC];
}

// @author Andre Allan Ponce
std::string ItemData::getItemName(int id){
	return data.at(id)[ITEM_NAME];
}

// @author Andre Allan Ponce
int ItemData::getSize(){
	return size;
}

// @author Andre Allan Ponce
void ItemData::setSize(int s){
	size = s;
}