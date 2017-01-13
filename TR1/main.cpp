#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <iterator>
#include <stdio.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

uint8_t map [10001][10001];

inline void scan(uint32_t* x)
{
	register char c = getchar_unlocked();
	*x = 0;
	for(; (c<48)||(c>57);c = getchar_unlocked());
	for(; (c>47)&&(c<58);c = getchar_unlocked())
		*x = (uint32_t)((((*x)<<1) + ((*x)<<3)) + c - 48);
}


int testCase(uint32_t numCity)
{
	uint32_t ind;
	list <uint32_t> path1, path2;
	
	
	
}

int main()
{
	uint32_t testCases, ind, numCity;
	
	scan(&testCases);
	
	for(ind=0;ind<testCases;ind++)
	{
		scan(&numCity);
	}
	return 0;
}