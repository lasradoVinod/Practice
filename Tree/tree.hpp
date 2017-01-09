#ifndef TREE_HPP
	#define TREE_HPP
	
	#include <stdint.h>
	
	template <typename T>
	class Tree
	{		
		public:
		virtual int addNode(T) = 0;
		virtual int deleteNode(T) = 0;
		virtual void traversal(uint32_t type) = 0;
	};
	
#endif