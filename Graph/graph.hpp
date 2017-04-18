#ifndef GRAPH_HPP
#define GRAPH_HPP
	
	#include <stdint.h>
	
	template <typename T, typename V>
	class Graph
	{		
		public:
		virtual void addEdge(T,T,V) = 0;
		virtual void deleteEdge(T,T) = 0;
		virtual void BFStraversal(T) = 0;
		virtual void DFStraversal(T) = 0;
	};
	
#endif