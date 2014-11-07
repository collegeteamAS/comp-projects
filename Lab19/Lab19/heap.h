#ifndef HEAP_H
#define HEAP_H

#include "task.h"
#include <iostream>
using namespace std;

class Heap
{
protected:
	Task *elements;
	int MAXSIZE;
	int currentSize;

	int parentInd(int index);
	int lChildInd(int index);
	int rChildInd(int index);
	Task parent(int index);
	Task lChild(int index);
	Task rChild(int index);
	
	void perculator(int index);
	void swapSpots(int first, int second);

public:
	Heap(int MAX = 10);

	void insert(Task item);
	Task pop();
	void print();
};

#endif
