
#ifndef _BEDROOM_H_INCLUDED_
#define _BEDROOM_H_INCLUDED_

class Bedroom : public Location{
public:
	Bedroom();
	Bedroom(int idNum, int xCoord, int yCoord, int h, int w);
};

#endif