#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
#include <iterator>
#include <stdio.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

typedef list <uint32_t> PathList;


#define replace(u,v,c)  { imp[u][v] = c; imp[v][u] = c;	}

inline void scan(uint32_t* x)
{
	register char c = getchar_unlocked();
	*x = 0;
	for(; (c<48)||(c>57);c = getchar_unlocked());
	for(; (c>47)&&(c<58);c = getchar_unlocked())
		*x = (uint32_t)((((*x)<<1) + ((*x)<<3)) + c - 48);
}

int getPath(std::vector<PathList> map,uint32_t find, uint32_t prev, uint32_t curr, PathList &p)
{
	uint32_t ret;
	if(curr == find)
	{
		p.push_front(curr);
		return 0;
	}

	PathList::iterator iterator;
	for (iterator = map[curr].begin(); iterator != map[curr].end(); ++iterator)
	{
    	if(*iterator != prev)
    	{
    		ret = getPath(map,find,curr,*iterator,p);
    		if(ret == 0)
    		{
    			p.push_front(curr);
    			return 0;
    		}
    	}
	}
	return -1;
}

void displayPath(PathList p)
{
	std::list<uint32_t>::const_iterator iterator;
	for (iterator = p.begin(); iterator != p.end(); ++iterator) {
    	std::cout << *iterator;
	}
}

int testCase(uint32_t numCity)
{
	unsigned long long sum=0;
	uint32_t ind,iInd,u,v,temp;
	PathList path1, path2;
	vector<PathList> map(numCity+1);
	vector<vector<uint32_t> > imp(numCity+1, vector<uint32_t>(numCity+1));
	vector <uint32_t> weight(numCity+1);
	
	for(ind=1;ind < numCity ; ind++)
	{
		scan(&u);
		scan(&v);
		map[u].push_back(v);
		map[v].push_back(u);
	}

	for(ind=1;ind <= numCity ; ind++)
	{
		imp[ind][ind] = ind;
		for(iInd=ind+1;iInd <= numCity ; iInd++)
		{
			if(ind == 1)
			{
				replace(ind,iInd,1)
				continue;
			}
			getPath(map,iInd,0, 1, path1);
			getPath(map,ind,0,1,path2);

			std::list<uint32_t>::const_iterator iterator1, iterator2;

			for(iterator1 = path1.begin(), iterator2= path2.begin(); \
				*iterator1 == *iterator2; ++iterator1, ++ iterator2)
			{
				temp = *iterator1;
			}

			replace(ind,iInd,temp)

		}
	}

	for(ind=1;ind <= numCity ; ind++)
	{
		for(iInd=1;iInd <= numCity ; iInd++)
		{
			weight[imp[ind][iInd]]++;
		}
	}
	
	for(ind=1;ind<=numCity;ind++)
	{
		sum = (sum + (ind * weight[ind])) % 1000000007;
	}
	
	return sum;
}

int main()
{
	uint32_t testCases, ind, numCity;

	scan(&testCases);

	for(ind=0;ind<testCases;ind++)
	{
		scan(&numCity);
		cout << testCase(numCity) << endl;
	}
	return 0;
}