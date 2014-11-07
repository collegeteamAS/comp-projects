#include "task.h"

Task::Task(string s, int p)
{
	task = s;
	priority = p;
}

int Task::getPriority()
{
	return priority;
}

string Task::getTask()
{
	return task;
}

void Task::setPriority(int p)
{
	priority = p;
}

void Task::setTask(string s)
{
	task = s;
}

ostream& operator<< (ostream& out, Task t)
{
	out << t.getPriority() << ": " << t.getTask();
	return out;
}