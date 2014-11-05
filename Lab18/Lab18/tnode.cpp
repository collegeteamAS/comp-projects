#include "tnode.h"

TNode::TNode(int d, TNode* l, TNode* r) : 
	data(d), 
	lchild(l), 
	rchild(r){

}

int TNode::getData(){
	return data;
}

TNode* TNode::getLeft(){
	return lchild;
}

TNode* TNode::getRight(){
	return rchild;
}

void TNode::setData(int value){
	data = value;
}

// rewrite these so the check for zero first
void TNode::setLeft(TNode* left){
	lchild = left;
}

void TNode::setRight(TNode* right){
	rchild = right;
}