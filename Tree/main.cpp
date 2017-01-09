#include <iostream>
#include <stdint.h>
#include "tree.hpp"
#include "binaryTree.hpp"

using namespace std;

int main()
{
	BinaryTree bTree;
    Tree<uint16_t> * tree;
	tree = (Tree<uint16_t> *) &bTree;
	(*tree).addNode(5);
	(*tree).addNode(3);
	(*tree).addNode(10);
	(*tree).addNode(2);
	(*tree).addNode(4);
	(*tree).addNode(8);
	(*tree).addNode(12);
	(*tree).deleteNode(12);
	(*tree).traversal(BT_POSTORDER);
	return 0;
}