#include <iostream>
#include <stdint.h>
#include "tree.hpp"
#include "binaryTree.hpp"

using namespace std;

int main()
{
	uint16_t nodes[] = {25,75};
	BinaryTree bTree;
    Tree<uint16_t> * tree;
	tree = (Tree<uint16_t> *) &bTree;
	(*tree).addNode(100);
	(*tree).addNode(50);
	(*tree).addNode(150);
	(*tree).addNode(25);
	(*tree).addNode(75);
	(*tree).addNode(125);
	(*tree).addNode(175);
	(*tree).addNode(12);
	(*tree).addNode(37);
	(*tree).addNode(112);
	(*tree).addNode(137);
	(*tree).addNode(62);
	(*tree).addNode(87);
	(*tree).addNode(162);
	(*tree).addNode(187);
	(*tree).addNode(6);
	(*tree).addNode(18);
	(*tree).addNode(31);
	(*tree).addNode(42);
	(*tree).addNode(56);
	(*tree).addNode(68);

	bTree.traversal(BT_INORDER);
	cout << bTree.findAncestralNode(25,75);
	
	return 0;
}