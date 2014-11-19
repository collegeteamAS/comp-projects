/*//
	@author Andre Allan Ponce
	Microsft's c++ windows/desktop library includes an awesome way to 
	replace/write console output in certain coordinate locations
	This prevents the issue of clearing screen and printing, which is
	super laggy. In order to faciltate the process of replacing the 
	correct characters, I've built a linked list that will store a 
	replacement character and an (x,y) coordinate that will feed into
	a console buffered output thing that will use the coordinate and 
	replace the corresponding char with the replacement.
	Instead of regular print out, we add what we want changed to this list,
	and then the print method will go through this and replace
	what we need. Tis pretty neat.

	unfortunatley, this is unused at the moment.
	2014-10-30
//*/

#ifndef _COORDLIST_H_INCLUDED_
#define _COORDLIST_H_INCLUDED_

class Coord_Node;

class Coord_List{
private:
	Coord_Node* head;

public:
	Coord_List();

	void add_node(char c, int x, int y); // adds node to top of list

	Coord_Node* remove_node(); // removes first node everytim
};

#endif