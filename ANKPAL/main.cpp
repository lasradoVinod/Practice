#include <iostream>
#include <cstdio>
#include <cstring>
 
using namespace std;

#define getChar(string,i,j,index)    ((index >= i && index <= j) ? string[j - (index - i)] : string[index])

void ip(char * inp)
{
    int temp=getchar_unlocked();
    while(temp<'a'||temp>'z')
        temp=getchar_unlocked();
    while(temp>='a'&&temp<='z')
    {
        *inp = (char)temp;
        temp=getchar_unlocked();
        inp++;
    }
}

inline void scan(int* x)
{
	register char c = getchar_unlocked();
	*x = 0;
	for(; (c<48)||(c>57);c = getchar_unlocked());
	for(; (c>47)&&(c<58);c = getchar_unlocked())
		*x = (int)((((*x)<<1) + ((*x)<<3)) + c - 48);
}

int isPalindrome (char * string, int i, int j, int start, int end)
{
    char a, b;
	i--;
	j--;
	start --;
	end --;
	while(start <= end)
	{
		if(getChar(string,i,j,start) == getChar(string,i,j,end))
		{
			start ++;
			end --;
		}
		else
		{
			return -1;
		}
	}	
	return 0;
}

int main(void) {

	int i,j,k,l;
	unsigned int iter;
	unsigned int numTestCases;
	char input[100001];
	
	ip(input);
	scanf("%u",&numTestCases);
	
	for(iter = 0;iter < numTestCases ; iter ++ )
	{
		scan(&i);
		scan(&j);
		scan(&k);
		scan(&l);	
		
		if(isPalindrome(input,i,j,k,l) == 0)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}