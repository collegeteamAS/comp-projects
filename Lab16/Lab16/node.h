#ifndef _NODE_H_INCLUDED_
#define _NODE_H_INCLUDED_
//author steve suh
class Item;

class Node
{
	private:
		//next node
		Node* next;
		Item* itemPointing;//the item this node is pointing at.

	public:
		Node();

		Item* getItem();
		Node* get_next();

		void pointTo(Item* i);
		void set_next(Node* next_node);

};

#endif