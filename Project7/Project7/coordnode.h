/*//
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	2014-10-30
	Node that contains char to replace and coordinates of 
	this char
//*/
#ifndef _COORDNODE_H_INCLUDED_
#define _COORDNODE_H_INCLUDED_

class Coord_Node{
private:
	char replacement; // the char to replace with

	// the coordinates of this char
	int x;
	int y;

	// the next node
	// (0 means end of list)
	Coord_Node* next;

public:
	Coord_Node(char r, int x_c, int y_c);

	Coord_Node* get_next();
	char get_replacement(); 
	int get_x();
	int get_y();

	void set_next(Coord_Node* next_node);
};

#endif