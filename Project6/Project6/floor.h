
#ifndef _FLOOR_H_INCLUDED_
#define _FLOOR_H_INCLUDED_

class Location;

class Floor {
private:
	Location*** floor;

	// id of this floor
	// 0 - debug
	// 1 - basement
	// 2 - ground
	// 3 - upper
	int id;

	// each floor has a height and width
	static const int FLOOR_HEIGHT = 30;
	static const int FLOOR_WIDTH = 30;

public:
	Floor(int idNum);

	void createFloor();

	int getID();
	Location* getLoc(int x, int y);


	void setID(int idNum); // we probably dont need this
	void setLoc(Location* loc, int x, int y);
	void set_room_doors(int x, int y, bool value);
};

#endif