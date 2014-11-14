//FileName:		player.h
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the header for the player class

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player
{
	protected: //attributes usually go here
		string name;
		int age;

	public:  //method prototypes usually go here
		Player(string n = "Dan");

		//Set methods allow objects to change the attributes
		void setName(string n);
		void setAge(int a) {age = a;}

		//Get methods allow objects to tell us about their attributes
		string getName();
		int getAge() {return age;}

		//Functionality methods are additional actions of objects of the class
		void display();
};

#endif