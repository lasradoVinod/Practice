#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
#include <cmath>

using namespace std;

#define BASE				256
#define PRIME_NUMBER		2347

int hashCreate(const string i, unsigned int size)
{
	int it,retVal = 0;

	for (it = 0; it < (int)size; ++it)
	{
		retVal = ((retVal * BASE) + i[it]) % PRIME_NUMBER;
	}
	return retVal;
}
int hashUpdate(string i, int currentHash, unsigned int currentPos, unsigned int size, int h)
{
	int retVal = (BASE * (currentHash - (int)(i[currentPos]*h)) + i[currentPos+size])%PRIME_NUMBER;

	if (retVal < 0)
		retVal = (retVal + PRIME_NUMBER);
	return retVal;
}

int match(string i, string s, int pos)
{
	int len = s.length();
	int it;
	for (it = 0;it< len;it++)
	{
		if(i[pos+it] != s[it])
		{
			return -1;
		}
	}
	return 0;
}
void findSubString(string s,string i,list <unsigned char> &position)
{
	int it;
	int p = i.length() - s.length();
	if (p < 0)
		return;
	int lenS = s.length();
	int initHash = hashCreate(i,lenS);
	int subHash = hashCreate(s,lenS);
	int h = 1;

	for (it=0;it<lenS-1;it++)
		h = (h * BASE) % PRIME_NUMBER;

	for (it=0;it<p;it++)
	{
		if(subHash == initHash)
		{
			if(match(i,s,it) == 0)
			{
				position.push_back(it);
			}
		}
		initHash = hashUpdate(i,initHash,it,lenS,h);
	}

}
int main()
{
	list <unsigned char> position;
	list <unsigned char>::iterator It;

	findSubString(string("Vin"),string("P Vinod Lasrado Vinod"),position);

	for(It = position.begin();It != position.end();++It)
	{
		cout << (int)*It << endl;
	}

}
