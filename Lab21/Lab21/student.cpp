#include "student.h"
Student::Student()
{
	name = "none";
	id = -1;
	gpa = 0;
}

Student::Student(string n, int i = -1, double g = 0)
{
	name = n;
	if (i >= -1)
		id = i;
	else
		id = -1;
	if (g >=0 && g <= 4)
		gpa = g;
	else
		gpa = 0;
}

string Student::getName()
{
	return name;
}

int Student::getID()
{
	return id;
}

double Student::getGPA()
{
	return gpa;
}

void Student::setName(string n)
{
	name = n;
}

void Student::setID(int i)
{
	if (i >= -1)
		id = i;
}

void Student::setGPA(double g)
{
	if (g >=0 && g <= 4)
		gpa = g;
}

ostream& operator<< (ostream& out, Student s)
{
	out << s.getID() << "  " << s.getName() << "  " << s.getGPA();
	return out;
}
