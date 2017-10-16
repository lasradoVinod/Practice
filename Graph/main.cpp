#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "graph.hpp"
#include "GraphArr.hpp"

using namespace std;

void display (int * a, int count)
{
	int i,j;
	for(i=0;i<count;i++)
	{
		for(j=0;j<count;j++)
		{
			cout << a[j * count + i] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int weight[5][5] = {0}, parent[5][5]={0};
	GraphArr graphTest = GraphArr(5);
	setbuf (stdout,NULL);
	graphTest.addEdge(0,0,0);
	graphTest.addEdge(1,1,0);
	graphTest.addEdge(2,2,0);
	graphTest.addEdge(3,3,0);
	graphTest.addEdge(4,4,0);
	graphTest.addEdge(0,1,5);
	graphTest.addEdge(0,3,2);
	graphTest.addEdge(1,2,2);
	graphTest.addEdge(2,0,3);
	graphTest.addEdge(2,4,7);
	graphTest.addEdge(3,2,4);
	graphTest.addEdge(3,4,1);
	graphTest.addEdge(4,0,1);
	graphTest.addEdge(4,1,3);
	graphTest.display();
	graphTest.FloydWarshall((int*)weight,(int*)parent);
	display((int *)weight,5);
	cout <<  "\n";
	/*display((int *)parent,5);*/
    cout << graphTest.FindShortestDistance(0,4) << endl;

	return 0;
}