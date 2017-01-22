#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    *inp = '\0';
}

inline void scan(int* x)
{
	register char c = getchar_unlocked();
	*x = 0;
	for(; (c<48)||(c>57);c = getchar_unlocked());
	for(; (c>47)&&(c<58);c = getchar_unlocked())
		*x = (int)((((*x)<<1) + ((*x)<<3)) + c - 48);
}

int main(void) {

	char s[101];
	char t[101];
	int k,len_s, len_t,ind , minVal ,m ;

	ip(s);
	ip(t);
	scan(&k);

	len_s = strlen(s);
	len_t = strlen(t);
	if(k >= (len_s + len_t))
	{
		printf("Yes\n");
		exit(0);
	}

	minVal =len_s < len_t ? len_s : len_t ;

	for(ind=0;ind<minVal;ind++)
	{
		if(s[ind]!= t[ind])
			break;
	}

	m = k - (len_t - ind) - (len_s - ind);

	if((m >= 0) && ((m % 2) == 0))
	{
		printf("Yes");
		exit(0);
	}

	printf("No");
	return 0;
}