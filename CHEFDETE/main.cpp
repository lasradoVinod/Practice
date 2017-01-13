#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

inline void scan(uint32_t* x)
{
	register char c = getchar_unlocked();
	*x = 0;
	for(; (c<48)||(c>57);c = getchar_unlocked());
	for(; (c>47)&&(c<58);c = getchar_unlocked())
		*x = (uint32_t)((((*x)<<1) + ((*x)<<3)) + c - 48);
}

int main()
{
	uint32_t numPeople, ind, rep;
	int people[100001] = {0};
	
	scan(&numPeople);
	
	
	for(ind=0;ind<numPeople;ind++)
	{
		scan(&rep);
		people[rep] = 1;
	}
	
	for(ind=1;ind<=numPeople;ind++)
	{
		if(people[ind] == 0)
			printf("%d ",ind);
	}
}