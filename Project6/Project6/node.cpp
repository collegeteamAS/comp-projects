#include "node.h"

//steve suh
Node::Node()
{
	itemPointing = 0;
}


Node* Node::get_next(){
	return next;
}

void Node::set_next(Node* next_node)
{
	next = next_node->get_next();
}


char Node::get_replacement(){
	return replacement;
}


Item* Node::getItem()
{
	return itemPointing;
}

void Node::pointTo(Item* item)
{
	itemPointing = item;
}
