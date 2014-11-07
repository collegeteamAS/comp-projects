#include "heap.h"

/***** Accessors for Indices and Elements *****/

int Heap::parentInd(int index) { return (index-1) / 2; }
int Heap::lChildInd(int index) { return 2 * index + 1; }
int Heap::rChildInd(int index) { return 2 * index + 2; }

Task Heap::parent(int index) { return elements[(index-1)/2]; }
Task Heap::lChild(int index) { return elements[2 * index + 1]; }
Task Heap::rChild(int index) { return elements[2 * index + 2]; }

// Constructor
Heap::Heap(int MAX)
{
	elements = new Task[MAX];
	MAXSIZE = MAX;
	currentSize = 0;
}

void Heap::insert(Task x){
	elements[currentSize++] = x;
}

void Heap::perculator(int index){
	if(lChild(index).getPriority() < rChild(index).getPriority()){
		swapSpots(index, lChildInd(index));
		perculator(lchildInd(index));
	}
	else if(lChild(index).getPriority() > rChild(index).getPriority()){
		swapSpots(index, rChildInd(index));
		perculator(rChildInd(index));
	}
}

Task Heap::pop(){
	Task top = elements[0];
	elements[0] = elements[currentSize--];
	perculator(0);
	return top;
}

void Heap::print(){
	for(int i = 0; i <= currentSize; i++){
		std::cout << elements[i].getPriority() << ". " << elements[i].getTask() << "\n";
	}
}

void Heap::swapSpots(int first, int second){
	Task temp = elements[first];
	elements[first] = elements[second];
	elements[second] = temp;
}