#include <iostream>
#include <stdint.h>
#include <cstring>
#include <stdlib.h>
#include "graph.hpp"
#include "GraphArr.hpp"

#define MAX 999

GraphArr::GraphArr(uint16_t count)
{
	uint16_t i,j;
	numNodes = count;
	root = (int **)malloc(count * sizeof(int*));
	if(root == NULL)
		exit(1);
	for(i = 0; i < count ; i ++)
	{
		root[i] = (int*)malloc(count * sizeof(int));
		if(root[i] == NULL)
			exit(1);
		for (j=0;j<count;j++)
		{
			root[i][j] = MAX;
		}
	}
}

GraphArr::~GraphArr()
{
	uint16_t i;
	for(i = 0; i < numNodes ; i ++)
	{
		free(root[i]);
	}
	free(root);
}

void GraphArr::addEdge(uint32_t i, uint32_t j, int w)
{
	root[i][j] = w;
}

void GraphArr::deleteEdge(uint32_t i, uint32_t j)
{
	root[i][j] = MAX;
}

void GraphArr::BFStraversal(uint32_t base)
{

}

void GraphArr::DFStraversal(uint32_t base)
{
/*	uint16_t i;
	std::cout << base << std::endl;
	for(i = 0; i < numNodes; i++)
	{
		if(root[base][i] != MAX && visited[i] == 0)
		{
			visited[i] = 1;
			DFStraversal(i);
		}
	}
*/}

void GraphArr::FloydWarshall(int * dist, int * par)
{
	uint16_t i,j,k;

	for(i=0;i<numNodes;i++)
	{
		for(j=0;j<numNodes;j++)
		{
			dist[j * numNodes + i] = root[i][j];

			if(dist[j * numNodes + i] != MAX)
			{
				par[j * numNodes + i] = i;
			}
		}
	}


	for(k=0;k<numNodes;k++)
	{
		for(i=0;i<numNodes;i++)
		{
			for(j=0;j<numNodes;j++)
			{
				if(dist[j * numNodes + i] > dist[k * numNodes + i] + dist[j * numNodes + k])
				{
					dist[j * numNodes + i] = dist[k * numNodes + i] + dist[j * numNodes + k];
					par[j * numNodes + i] = k;
				}
			}
		}
	}
}

void GraphArr::display()
{
	uint16_t i,j;
	
	for(i = 0; i < numNodes; i++)
	{
		for(j = 0; j < numNodes; j++)
		{
			if (root[i][j] == MAX)
			{
				std::cout << "inf ";
			}
			else
			{
				std::cout << root[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
}