#include "node.h"
#include "item.h"

//steve suh
Node::Node():
	next(0),
	itemPointing(0){
}


Node* Node::get_next(){
	return next;
}

void Node::set_next(Node* next_node)
{
	next = next_node;
}

Item* Node::getItem()
{
	return itemPointing;
}

void Node::pointTo(Item* item)
{
	itemPointing = item;
}
