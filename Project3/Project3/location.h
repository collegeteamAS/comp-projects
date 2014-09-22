

#ifndef _LOCATION_H_INCLUDED_
#define _LOCATION_H_INCLUDED_

using namespace std;

class Location{
protected:
	bool visited;
	char symbol;

public:
	Location();
	Location(char s);
	bool getVisited();
	char getSymbol();

	void setVisited(bool vis);
	void setSymbol(char sym);

	virtual std::string draw() = 0;
	//virtual int visit(Player &p);
};

#endif