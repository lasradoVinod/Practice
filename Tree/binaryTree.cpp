#include <iostream>
#include <stdint.h>
#include <queue>
#include "binaryTree.hpp"


BinaryTree::BinaryTree()
{
	root = 0;
}

static void initRoot(TreeNode ** const root, uint16_t data)
{
	*root =  new TreeNode;
	(*root)->data = data;
	(*root)->left = NULL;
	(*root)->right = NULL;
}

BinaryTree::BinaryTree(uint16_t data)
{
	initRoot(&root,data);
}

BinaryTree::~BinaryTree()
{
	//TODO: To be implemented after implementation of traversal;
}

int BinaryTree::addNode(uint16_t data)
{
	TreeNode * pointer = root, *q;
	if(root == 0)
	{
		initRoot(&root,data);
		return 0;
	}
	while(1)
	{
		if(pointer->data == data)
		{
			return -1;
		}
		if(pointer->data < data && pointer->right == NULL)
		{
				q = (TreeNode*) new TreeNode;
				q->data = data;
				q->left = 0;
				q->right = 0;
				pointer->right=q;
				return 0;
		}
		
		if(pointer->data > data && pointer->left == NULL)
		{
				q = (TreeNode*) new TreeNode;
				q->data = data;
				q->left = 0;
				q->right = 0;
				pointer->left=q;
				return 0;
		}
		if(pointer->data > data && pointer->left != NULL)
		{
			pointer = pointer->left;
		}
		
		if(pointer->data < data && pointer->right != NULL)
		{
			pointer = pointer->right;
		}		
	}
	
}

int BinaryTree::deleteNode(uint16_t data)
{
	TreeNode * pointer = root, * temp,*parent;
	if(root == 0)
	{
		return -1;
	}
	while(1)
	{
		if(pointer->data == data)
		{
			if(pointer->right != NULL && pointer->left != NULL)
			{	
				parent = pointer;
				temp = pointer->right;
				while(temp->left != NULL)
				{
					parent = temp;
					temp = temp->left;
				}
				pointer->data = temp->data;
				if(parent != pointer)
				{
					delete(parent->left);
					parent->left = NULL;
				}
				else
				{
					delete(parent->right);
					parent->right = NULL;
				}
			}
			else if(pointer->left == NULL && pointer->right == NULL)
			{
				if (pointer == root)
				{
					delete(root);
					root = NULL;
					return 0;
				}
				if(parent->data > pointer->data)
				{
					delete(parent->left);
					parent->left = NULL;
					return 0;
				}
				else
				{
					delete(parent->right);
					parent->right = NULL;
					return 0;
				}
			}
			else
			{
				if (pointer == root)
				{
					temp = root;
					if(pointer->left == NULL)
						root = pointer->right;
					else
						root = pointer->left;
					delete(root);
					return 0;
				}
				if(parent->data > pointer->data)
				{
					if(pointer->left == NULL)
						parent->left = pointer->right;
					else
						parent->left = pointer->left;
					
					delete(pointer);					
					return 0;
				}
				else
				{
					if(pointer->left == NULL)
						parent->right = pointer->right;
					else
						parent->right = pointer->left;
					delete(pointer);					
					return 0;
				}
			}
		}
		if(pointer->data > data)
		{
			if(pointer->left == NULL)
				return -1;
			parent = pointer;
			pointer = pointer->left;
		}
		if(pointer->data < data)
		{
			if(pointer->right == NULL)
				return -1;
			parent = pointer;
			pointer = pointer->right;
		}	
	}
}

void traverse(TreeNode const * const pointer, uint32_t type)
{
	if(type != BT_PREORDER)
	{
		if(pointer->left == NULL && pointer->right == NULL )
		{
			std::cout << pointer->data << "->" ;
			return;
		}
	}
	else
	{
		std::cout << pointer->data << "->" ;
	}
	
	if(pointer->left != NULL)
	{
		traverse(pointer->left,type);
	}
	if(type == BT_INORDER)
	{
		std::cout << pointer->data << "->" ;
	}
	if(pointer->right != NULL)
	{
		traverse(pointer->right,type);
	}
	if(type == BT_POSTORDER)
	{
		std::cout << pointer->data << "->" ;
	}
	return;
}


void BinaryTree::traversal(uint32_t type)
{
	traverse (root,type);
}

static TreeNode * findAnsNode( TreeNode * node,uint16_t d1, uint16_t d2)
{
	if (node->data == d1 || node->data == d2)
		return node;

	TreeNode * n1;
	TreeNode * n2;
	if (node->left != NULL)
		n1 = findAnsNode(node->left,d1,d2);
	else
	    return NULL;

	if (node->right != NULL)
		n2 = findAnsNode(node->right,d1,d2);
	else
	  return NULL;

	if (n1 != NULL && n2 != NULL)
		return node;
	else
		return n1 == NULL ? n2 : n1;
}

uint16_t BinaryTree::findAncestralNode(uint16_t d1, uint16_t d2)
{
	return findAnsNode(root,d1,d2)->data;
}
