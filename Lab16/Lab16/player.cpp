//FileName:		player.cpp
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the methods for the player class

#include "player.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Player::Player(string n)
{
	name = n;
	age = 0;
}

void Player::setName(string n)
{
	name = n;
}

string Player::getName()
{
	return name;
}

void Player::display()
{
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
}