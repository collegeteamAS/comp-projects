
#include "coordnode.h"

Coord_Node::Coord_Node(char r, int x_c, int y_c) :
	replacement(r),
	x(x_c),
	y(y_c),
	next(0){

}

Coord_Node* Coord_Node::get_next(){
	return next;
}

char Coord_Node::get_replacement(){
	return replacement;
}

int Coord_Node::get_x(){
	return x;
}

int Coord_Node::get_y(){
	return y;
}