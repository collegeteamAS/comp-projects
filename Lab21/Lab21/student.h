#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;

class Student
{
protected:
	string name;
	int id;
	double gpa;
public:
	Student();
	Student(string n, int i, double g);
	string getName();
	int getID();
	double getGPA();
	void setName(string n);
	void setID(int i);
	void setGPA(double g);
};

ostream& operator<< (ostream& out, Student s);

#endif