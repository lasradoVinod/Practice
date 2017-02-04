#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#define MAX_FIND(a,b)   (a>b?a:b)

using namespace std;


inline void scan(int* x)
{
	register char c = getchar_unlocked();
	*x = 0;
	for(; (c<48)||(c>57);c = getchar_unlocked());
	for(; (c>47)&&(c<58);c = getchar_unlocked())
		*x = (int)((((*x)<<1) + ((*x)<<3)) + c - 48);
}

int main()
{
	int numCases, oInd, ind;
	int numPeople,temp,pos,sum;
	scan(&numCases);
	std::vector<int> *q, *b; 
	for(oInd = 0;oInd < numCases; oInd ++)
	{
		sum=0;
		scan(&numPeople);
		q = new vector<int>();
		b = new vector<int>();
		for(ind=1;ind<numPeople + 1;ind ++)
		{
			scan(&temp);
			q->push_back(temp);
			b->push_back(ind);
		}	

		for(ind = 0; (ind < numPeople); ind++)
		{
			if((*q)[ind] == (*b)[ind])
			{
				continue;
			}
			pos = find (b->begin()+ind+1, b->end(), (*q)[ind]) -b->begin();
			if(pos-ind <= 2)
			{
				 sum += pos-ind;
			     b->insert(b->begin()+ind,(*q)[ind]); 
                 b->erase(b->begin() + pos + 1);
			}
            else
            {
                cout <<"Too chaotic" << endl;
				break;
            }
		}
		if(ind == numPeople)
			cout << sum << endl;      
	}
    return 0;
}