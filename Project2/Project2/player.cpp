/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Player class
*/

#include <string>
#include <sstream> // converting ints to strings takes some work
//#include <iostream>
#include "player.h"

using namespace std;

// @author Andre Allan Ponce
Player::Player() : name("debug"), age(-1){
	// constructors should be empty, yo
}

// @author Andre Allan Ponce
Player::Player(string n, int a) : name(n), age(a){
	// constructors should be empty, yo
}

// @author Andre Allan Ponce
int Player::getAge(){
	return age;
}

// @author Andre Allan Ponce
string Player::getName(){
	return name;
}

// @author Andre Allan Ponce
string Player::print(){
	ostringstream temp;
	temp << age;
	return "Name: "+name+"\n"
		"Age: "+temp.str()+"\n";
}

// @author Andre Allan Ponce
void Player::setAge(int a){
	age = a;
}

// @author Andre Allan Ponce
void Player::setName(string n){
	name = n;
}