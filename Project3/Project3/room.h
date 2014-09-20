
#ifndef _ROOM_H_INCLUDED_
#define _ROOM_H_INCLUDED_

class Room : public Location{
protected:
	int id;
	std::vector<std::vector<char>> roomLayout; // visualization of the room

	// where this room is
	int x; 
	int y;

	// rooms with closets have importance
	bool hasCloset;

	// rooms got some size
	int width;
	int height;

	// -1 means no door, num >= 0 means row/col of door
	int leftDoorRow;
	int rightDoorRow;
	int upDoorCol;
	int downDoorCol;

public:
	Room();
	Room(int idNum, int xCoord, int yCoord, int h, int w);
	//~Room();

	bool doesRoomHaveCloset();
	virtual std::string draw();
	void fillArray(std::string layout);

	int getHeight();
	int getRoomID();
	int getWidth();
	int getX();
	int getY();

	void setRoomCloset(bool value);
	void setRoomID(int idNum);
	void setDownDoorCol(int c);
	void setLeftDoorRow(int r);
	void setRightDoorRow(int r);
	void setUpDoorCol(int c);
};

#endif