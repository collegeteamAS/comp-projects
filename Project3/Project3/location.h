/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	(20% done by steve)
*/

#ifndef _LOCATION_H_INCLUDED_
#define _LOCATION_H_INCLUDED_

#include <string>

class Location{
protected:
	bool visited;

	int id;
	char** roomLayout; // visualization of the room
	// roomLayout(0,std::vector<char>(0,'0'))

	// rooms with closets have importance
	bool hasCloset;

	// rooms with only one door are closed
	bool isClosed;

	// rooms got some size
	int width;
	int height;

	// where this location is
	int x; 
	int y;

public:
	enum Contsants{
		EMPTY_SPACE = ' '
	};
	
	Location();
	Location(int idNum, int xCoord, int yCoord, int h, int w, bool closet, bool closed);
	//~Room(); this is giving some issues right now

	void createArray(); // height and width should be set, already
	void deleteArray();
	bool doesRoomHaveCloset();
	virtual std::string draw();
	void fillArray(char** room); // dont forget to fill the array

	int getHeight();
	int getRoomID();
	char getSpaceAt(int xCoord, int yCoord);
	int getWidth();

	bool isRoomClosed();
	bool movePlayer(int xOld, int yOld, char player, int xNew, int yNew); // this moves player to new spot (if valid) and updates the array
	void resetSpace(int xSpace, int ySpace, char space);
	void setPlayer(int xPlay, int yPlay, char player);

	//void setRoomCloset(bool value);
	void setRoomID(int idNum);
};

#endif