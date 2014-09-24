#ifndef ORB_H
#define ORB_H
#include <string>
#include <iostream>


using namespace std;

class Orb : public Location
{
private:
	bool taken;

public:
	Orb();
	Orb(char s);
	virtual void draw();
	virtual int visit(Player &p);
};

#endif