#include <string>
#include <iostream>
#include "blood.h"
#include "constants.cpp"

using namespace std;

Blood::Blood()
{
	symbol = '*';
	description = ROOMITEM_BLOOD;
}