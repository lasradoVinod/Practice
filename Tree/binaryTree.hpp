#ifndef BINARY_TREE_HPP
	#define BINARY_TREE_HPP

#include <iostream>
#include <stdint.h>
#include "tree.hpp"

#define BT_INORDER			0
#define BT_POSTORDER		1
#define BT_PREORDER			2

typedef struct __treeNode
{
	uint16_t data;
	struct __treeNode * left;
	struct __treeNode * right;
}TreeNode;

class BinaryTree: public Tree <uint16_t>
{
	TreeNode * root;
	
	public:
		BinaryTree();
		BinaryTree(uint16_t);
		~BinaryTree();
		int addNode(uint16_t);
        int deleteNode(uint16_t);
		void traversal(uint32_t type);
		uint16_t findAncestralNode(uint16_t d1, uint16_t d2);
};      
                      
#endif