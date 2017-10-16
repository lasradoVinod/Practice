#include <iostream>
#include <stdint.h>
#include <cstring>
#include <list>
#include <vector>
#include <iterator>
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
	uint16_t i,curr;
	uint8_t * visited = (uint8_t *)malloc(numNodes * sizeof(uint8_t));

	for (i=0;i<numNodes;i++)
	{
		visited[i] = (uint8_t)0;
	}
	std::list<uint32_t> nodes ;
	nodes.push_front(base);
	
	std::cout << base << std::endl;
	visited[base] = (uint8_t)1;
	while(!nodes.empty())
	{
		curr = *(nodes.begin());
		nodes.pop_front();

		for(i =0; i<numNodes ; i++)
		{
			if(root[curr][i] != MAX && visited[i] != 1)
			{
				visited[i] = (uint8_t)1;
				std::cout << i << std::endl;
				nodes.push_back(i);
			}	
		}
	}
}

void GraphArr::DFStraversal(uint32_t base)
{
	uint16_t i,curr;
	uint8_t * visited = (uint8_t *)malloc(numNodes * sizeof(uint8_t));
	std::list<uint32_t> nodes ;
	nodes.push_front(base);

	for (i=0;i<numNodes;i++)
	{
		visited[i] = 0;
	}

	while(!nodes.empty())
	{
		curr = *(nodes.begin());
		nodes.pop_front();

		if (visited[curr] == 1)
		{
			continue;
		}

		visited[curr] = 1;
		std::cout << curr << std::endl;
		for(i =0; i<numNodes ; i++)
		{
			if(root[curr][i] != MAX && visited[i] != 1)
				nodes.push_front(i);				
		}
	}
}

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

uint32_t GraphArr::FindShortestDistance(uint32_t start, uint32_t end)
{
	std::vector<uint8_t> v(numNodes,0);
	std::vector<uint32_t> d(numNodes,MAX);

	int i;
	int currNode = start;
	v[start] = 1;
	d[start] = 0;
	int minLength = MAX;
	int minIndex = -1;
	while(1)
	{
		minLength = MAX;
		minIndex = -1;
		for (i=0;i<numNodes;i++)
		{
			if (v[i] == 0 && (root[currNode][i] + d[currNode] < d[i]))
			{
				d[i] = root[currNode][i] + d[currNode];
				minLength = d[i];
				minIndex = i;


			}
			for (int j=0;j<numNodes;j++)
			{
				std::cout << d[j] << " " ;
			}
			std::cout << std::endl;
		}
		if (minIndex == -1)
			break;

		currNode = minIndex;
		v[currNode] = 1;
	}
	return d[end];
}
