#ifndef CRYSTAL_H
#define CRYSTAL_H
#include <string>
#include <iostream>

using namespace std;

class Crystal : public Location
{
private:
	bool taken;

public:
	Crystal();
	Crystal(char s);
	virtual void draw();
	virtual int visit(Player &p);
};

#endif