#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player{
private:
	string name;
	int age;

public:
	Player();

	int getAge();
	string getName();

	void print();

	void setAge(int a);
	void setName(string n);

};

#endif