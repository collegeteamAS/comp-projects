#include <string>
#include <iostream>
#include "player.h"
#include "location.h"
#include "orb.h"
#include "crystal.h"

using namespace std;

int main()
{
	Location *lPtr = new Location('l');
	Crystal *cPtr = new Crystal('c');
	Orb *oPtr = new Orb('o');
	Player *pPtr = new Player();

		lPtr[0].draw();
		cPtr[0].draw();
		oPtr[0].draw();

		cout << lPtr[0].visit(pPtr[0]);
		cout << cPtr[0].visit(pPtr[0]);
		cout << oPtr[0].visit(pPtr[0]);

		lPtr[0].draw();
		cPtr[0].draw();
		oPtr[0].draw();
}
