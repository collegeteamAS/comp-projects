/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	2014-10-30
//*/

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
		new_node->set_next(head);
		head = new_node;
	}
}

Coord_Node* Coord_List::remove_node(){
	if(head == 0){
		return head;
	}
	Coord_Node* removal = head;
	head = removal->get_next();
	removal->set_next(0);
	return removal;
}