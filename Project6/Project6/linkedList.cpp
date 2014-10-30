#include "linkedList.h"
#include "node.h"
/*Steve Suh
h_suh@u.pacific.edu
2014-10-29

*/
LinkedList::LinkedList()
{
	head = 0;
	numKeys = 0;
}

int LinkedList::getNumKeys()
{
	return numKeys;
}

void LinkedList::add_node(Node* n)
{
	while(head != 0)
	{
		Node* new_node = new Node();
		new_node->set_next(head->get_next()); //a node pointer new_node is set to the second place(next
		head = new_node;
	}

	if(head == 0)
	{
		head = n;
		if(head->getItem()->getID() == 1) //if the node is a key
		{
			numKeys++; //add 1 to the count
		}
	}
}

Node* LinkedList::remove_node(){
	Node* removal = head;
	head = removal->get_next();
	removal->set_next(0);
	return removal;
}

void LinkedList::displayList()
{

}
