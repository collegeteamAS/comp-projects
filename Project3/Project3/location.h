

#ifndef _LOCATION_H_INCLUDED_
#define _LOCATION_H_INCLUDED_

class Location{
protected:
	bool visited;

	// where this location is
	int x; 
	int y;

public:
	enum Contsants{
		EMPTY_SPACE = ' '
	};

	bool isEmpty(int xCoord, int yCoord);

	Location();
	Location(int xCoord, int yCoord);

	bool getVisited();
	
	int getX();
	int getY();

	void setVisited(bool vis);

	virtual std::string draw() = 0;
	//virtual int visit(Player &p);
};

#endif