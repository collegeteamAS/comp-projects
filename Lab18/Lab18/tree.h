#ifndef TREE_H
#define TREE_H

class TNode;

class Tree
{
protected:
	TNode* root;
	
	void addNode(TNode* node);
	void insertValue(TNode* node, int num);
	void printNode(TNode* node, bool leaf);
	void printNodeBranch(TNode* node, bool leaf);
	
public:
	Tree(TNode* r = 0);
	
	void addLayer();
	/*// adds two children to leaf nodes
	left child stores (leaf_node).data-1;
	right child stores (leaf_node).data+1;
	no need to check if we have duplicate data
	//*/
	
	void insert(int x);
	void print();
	/*// prints data in tree using
		pre-order traversal
	//*/
	
	void printLeaves();
	/*// prints data in only leaves
	//*/
};

#endif 