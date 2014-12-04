//coded by steve suh

#ifndef _LINKEDLIST_H_INCLUDED_
#define _LINKEDLIST_H_INCLUDED_

#include <string>

class Node;

class LinkedList
{
	private:
		Node* head;
		int numKeys; //this will keep track of the number of keys that player has

	public:
		LinkedList();
		~LinkedList();

		void add_node(Node* n);
		std::string displayInventory();
		Node* remove_node(); // removes first node everytime
		Node* remove_node(int id); // removes node based on id
		int getNumKeys(); //get the number of how many keys player currently has.
};

#endif