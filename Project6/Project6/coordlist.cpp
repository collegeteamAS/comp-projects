
#include "coordlist.h"
#include "coordnode.h"

Coord_List::Coord_List() : head(0){

}

void Coord_List::add_node(char c, int x, int y){
	if(head == 0){
		head = new Coord_Node(c,x,y);
	}
	else{
		Coord_Node* new_node = new Coord_Node(c,x,y);
		new_node->set_next(head->get_next());
		head = new_node;
	}
}

Coord_Node* Coord_List::remove_node(){
	Coord_Node* removal = head;
	head = removal->get_next();
	removal->set_next(0);
	return removal;
}