#include <string>
#include "linkedList.h"
#include "node.h"
#include "item.h"
#include "menutext.h"


/*Steve Suh
h_suh@u.pacific.edu
2014-10-29

*/

LinkedList::LinkedList()
{
	head = 0;
	numKeys = 0;
}

LinkedList::~LinkedList(){
	while(head != 0){
		Node* removed = remove_node();
		delete removed;
	}
}

int LinkedList::getNumKeys()
{
	return numKeys;
}

void LinkedList::add_node(Node* n)
{
	if(head == 0){
		head = n;
	}
	else{
		n->set_next(head);
		head = n;
	}
	if(n->getItem()->getID() == Item::ID_KEY) //if the node is a key
	{
		numKeys++; //add 1 to the count
	}
}

Node* LinkedList::remove_node(){
	if(head == 0){
		return head;
	}
	Node* removal = head;
	head = removal->get_next();
	removal->set_next(0);
	if(removal->getItem()->getID() == Item::ID_KEY){
		numKeys--;
	}
	return removal;
}

Node* LinkedList::remove_node(int id){
	if(head->get_next() == 0){
		if(head->getItem()->getID() == id){
			Node* temp = head;
			head = 0;
			if(id == Item::ID_KEY){
				numKeys--;
			}
			return temp;
		}
	}
	else if(head != 0){
		Node* next = head;
		while(next->get_next()->getItem()->getID() != id && next->get_next() != 0){
			next = next->get_next();
		}
		if(next->get_next() != 0){
			Node* temp = next->get_next();
			next->set_next(temp->get_next());
			temp->set_next(0);
			if(id == Item::ID_KEY){
				numKeys--;
			}
			return temp;
		}
	}
	return head;	
}

std::string LinkedList::displayInventory()
{
	std::string inventory = MenuText::PLAYER_INVENTORY_EMPTY;
	if (numKeys == 1)
		inventory = MenuText::PLAYER_INVENTORY_KEY_1;
	if (numKeys == 2)
		inventory = MenuText::PLAYER_INVENTORY_KEY_2;
	if (numKeys == 3)
		inventory = MenuText::PLAYER_INVENTORY_KEY_3;
	return inventory;
}
