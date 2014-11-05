#include <iostream>
#include <random>
#include "tree.h"
#include "tnode.h"


Tree::Tree(TNode *r) : 
	root(r){
	
}

void Tree::addLayer(){
	if(root != 0){
		addNode(root);
	}
	else{
		random_device rd;
		int randomData = (rd() % 100) +1;
		root = new TNode(randomData,0,0);
	}
}

void Tree::addNode(TNode* node){
	if(node->getLeft() != 0){
		addNode(node->getLeft());
	}
	if(node->getRight() != 0){
		addNode(node->getRight());
	}
	else{
		node->setLeft(new TNode(node->getData()-1,0,0));
		node->setRight(new TNode(node->getData()+1,0,0));
	}
}

void Tree::insert(int x){
	insertValue(root,x);
}

void Tree::insertValue(TNode* node, int num){
	if(node == 0){
		node = new TNode(num,0,0);
	}
	else if(node->getData() > num){
		insertValue(node->getLeft(),num);
	}
	else if(node->getData() < num){
		insertValue(node->getRight(),num);
	}
	else{
		// number is the same. not sure what we will do here
	}
}

void Tree::print(){
	if(root != 0){
		printNode(root, false);	
	}
	else{
		std::cout << "we don't have no tree";
	}
}

void Tree::printLeaves(){
	if(root != 0){
		printNode(root, true);
	}
	else{
		std::cout << "we don't have no tree";
	}
}

void Tree::printNode(TNode* node, bool leaf){
	if(!leaf){
		std::cout << node->getData();
		printNodeBranch(node,leaf);
	}
	else{
		if(node->getLeft() != 0 || node->getRight() != 0){
			printNodeBranch(node,leaf)
		}
		else{
			std::cout << node->getData();
		}
	}
}

void Tree::printNodeBranch(TNode* node, bool leaf){
	if(node->getLeft() != 0){
		printNode(node->getLeft(),leaf);
	}
	if(node->getRight() != 0){
		printNode(node->getRight(),leaf)
	}
}