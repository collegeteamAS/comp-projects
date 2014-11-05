#ifndef TNODE_H
#define TNODE_H

#include <iostream>
using namespace std;

class TNode
{
protected:
	int data;
	TNode *lchild, *rchild;
public:
	TNode(int d = -1, TNode* l = 0, TNode* r = 0);
	
	int getData();
	TNode* getLeft();
	TNode* getRight();
	
	void setData(int value);
	void setLeft(TNode* left);
	void setRight(TNode* right);
};

#endif