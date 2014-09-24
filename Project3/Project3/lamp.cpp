#include <string>
#include <iostream>
#include "lamp.h"
#include "constants.cpp"

using namespace std;

Lamp::Lamp()
{
	symbol = 'l';
	description = ROOMITEM_LAMP;
}