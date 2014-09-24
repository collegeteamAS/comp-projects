
#ifndef _ROOM_H_INCLUDED_
#define _ROOM_H_INCLUDED_

#include <string>
#include <vector>
#include "location.h"

class Room : public Location{
protected:
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

public:
	

	Room();
	Room(int idNum, int xCoord, int yCoord, int h, int w, bool closet, bool closed);
	//~Room(); this is giving some issues right now

	void createArray(); // height and width should be set, already
	void deleteArray();
	bool doesRoomHaveCloset();
	virtual std::string draw();
	//void fillArray(std::stringstream& in);
	void fillArrayRow(std::string line, int row);

	int getHeight();
	int getRoomID();
	char getSpaceAt(int xCoord, int yCoord);
	int getWidth();

	bool isRoomClosed();
	friend bool movePlayer(int xOld, int yOld, char player, int xNew, int yNew);
	friend void resetSpace(int xSpace, int ySpace, char space);
	friend void setPlayer(int xPlay, int yPlay, char player);

	//void setRoomCloset(bool value);
	void setRoomID(int idNum);
};

#endif