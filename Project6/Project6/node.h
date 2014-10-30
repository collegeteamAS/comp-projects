#ifndef _NODE_H_INCLUDED_
#define _NODE_H_INCLUDED_
//author steve suh
#include "item.h"

class Node
{
	private:

		//char for the replacement
		char replacement; 

		//next node
		Node* next;
		Item* itemPointing;//the item this node is pointing at.

	public:
		Node();
		Item* getItem();

		Node* get_next();
		char get_replacement(); 

		void pointTo(Item* i);
		void set_next(Node* next_node);

};

#endif