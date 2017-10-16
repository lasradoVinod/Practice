#ifndef GRAPH_ARRAY_HPP
	#define GRAPH_ARRAY_HPP

#include <iostream>
#include <stdint.h>
#include "graph.hpp"


class GraphArr: public Graph <uint32_t, int>
{
	private:
		int numNodes;
		int ** root;
		int *visited;
	
	public:
		GraphArr(uint16_t);
		~GraphArr();
		void addEdge(uint32_t, uint32_t, int);
        void deleteEdge(uint32_t, uint32_t);
		void BFStraversal(uint32_t);
		void DFStraversal(uint32_t);
		void display();
		void FloydWarshall(int * dist, int * par);
	    uint32_t FindShortestDistance(uint32_t root, uint32_t end);
}; 
                      
#endif