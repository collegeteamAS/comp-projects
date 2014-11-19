/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	2014-10-30
	(20% done by steve)
*/

#ifndef _LOCATION_H_INCLUDED_
#define _LOCATION_H_INCLUDED_

#include <string>
class LinkedList;
class Node;

class Location{
protected:
	bool visited; // now actually used sorta

	bool endGame; // is this room the endGame room? used for debugging

	LinkedList* items; // the items in this room

	int id;
	// id of this room

	char** roomLayout; // visualization of the room
	// roomLayout(0,std::vector<char>(0,'0'))

	// rooms with closets have importance
	//bool hasCloset;

	// rooms with only one door are closed
	//bool isClosed;

	// where this location is
	int x; 
	int y;

	// door placement // not very important it turns out.
	bool has_east_door;
	bool has_north_door;
	bool has_south_door;
	bool has_west_door;

	void deleteItems();
	void deleteLayout();

public:
	
	Location();
	Location(int idNum, int xCoord, int yCoord);
	~Location();

	virtual void addItem(Node* n);
	virtual void addKey() = 0; // adds a key
	virtual void createNewArray(char*** room) = 0; // height and width should be set, already
	virtual char*** draw() = 0;

	// getting the doors
	bool get_east_door();
	bool get_north_door();
	bool get_south_door();
	bool get_west_door();

	int getHeight();
	virtual Node* getItem(int id);
	virtual int getNumOfKeys();
	int getRoomID();
	int getWidth();
	bool isFinalRoom(); // for debug
	virtual void setFinalRoom(bool value);
	void setRoomID(int idNum);

	// setting the doors
	void set_east_door(bool value);
	void set_north_door(bool value);
	void set_south_door(bool value);
	void set_west_door(bool value);
};

#endif