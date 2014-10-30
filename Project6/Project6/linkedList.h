//coded by steve suh

#ifndef _LINKEDLIST_H_INCLUDED_
#define _LINKEDLIST_H_INCLUDED_

#include "node.h"

class LinkedList
{
	private:
		Node* head;
		int numKeys; //this will keep track of the number of keys that player has
		void displayInventory();
	public:
		LinkedList();
		void add_node(Node* n);
		Node* remove_node(); // removes first node everytime
		int getNumKeys(); //get the number of how many keys player currently has.

};

#endif