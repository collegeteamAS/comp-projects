/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	2014-10-30
	this holds the layouts for the tiles

	2014-12-03
	+ added the rules for tile creation
*/

#ifndef _LOCATIONDATA_H_INCLUDED_
#define _LOCATIONDATA_H_INCLUDED_

#include <unordered_map>

class LocationData{
private:
	std::unordered_map<int,char**> data; // each room's layouts
	int size; // how many items in this list

public:
	enum Constants{
		TILE_BASIC = 0,		// also known as debug
		TILE_NORTH = 1,		// 1 North edge location
		TILE_EAST = 2,		// 2 East edge location
		TILE_SOUTH = 3,		// 3 South Edge Location
		TILE_WEST = 4,		// 4 West edge location
		TILE_NORTH_EAST = 5,// 5 North East location
		TILE_SOUTH_EAST = 6,// 6 South East location
		TILE_SOUTH_WEST = 7,// 7 South West location
		TILE_NORTH_WEST = 8 // 8 North West location
	};

	LocationData();
	LocationData(int amount);

	void createMaps(int amount); // not sure if we need this
	void fillRoom(int id, int rows, int cols, char*** room);
	/*// fills one element of the map
	@param id - the id of the map element to fill (also the index and key)
	@param rows - the number of rows of this element
	@param cols - the number of cols of this element
	@param room - pointer to the 2d array of the layout to put in this map.
	//*/

	int getSize();
	char*** retrieveRoom(int id);
	/*// gets the room layout of id
	@param id - the id/key/index of the room to retrieve
	@return a pointer to the 2d array of the layout
	//*/

	void setSize(int num);
};

#endif