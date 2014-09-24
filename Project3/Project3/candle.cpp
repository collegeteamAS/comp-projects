#include <string>
#include <iostream>
#include "candle.h"
#include "constants.cpp"

using namespace std;

Candle::Candle()
{
	symbol = 'I';
	description = ROOMITEM_CANDLE;
}