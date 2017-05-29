#include <stdio.h>

#define TOUPPER(x)  (x>96 ? x-32:x)
#define ISUPPER(x)  (x<91 ? 1:0)
#define ISLOWER(x)  (x>96 ? 1:0)

int scan(char* x)
{
    int i,lastUpper;
	register char c = getchar_unlocked();
	*x = 0;
	for(; !(((c>64)&&(c<91)) || ((c>96)&&(c<123)));c = getchar_unlocked());
	for(; (((c>64)&&(c<91)) || ((c>96)&&(c<123)));c = getchar_unlocked())
	{
        *(x+i) = c;
        if(ISUPPER(c))
        {
            lastUpper == i;
        }
        i++;
    }
    *(x+i) = '\0';
    return lastUpper;
}

int main()
{
    int q,i,j,lA;
    int currA,currB;
    char a[1001], b[1001];
    char done = 0;
    scanf ("%d",&q);
    
    for (i=0;i<q;i++)
    {
        lA = scan(a);
        scan(b);
        
        currB = 0;
        currA = -1;
        
        for (j=0;a[j]!='\0';j++)
        {
            if(currA == -1)
            {
                if(b[currB] == TOUPPER(a[j]))
                {
                    currA = j;
                    currB++;
                    if(b[currB] == '\0')
                    {
                        if (j >= lA)
                        {
                            done = 1;
                            break;
                        }
                        else
                        {
                            j = currA;
                            currA = -1;
                            currB = 0;
                            continue;
                        }
                    }
                    continue;
                }
            }
            
            if(ISUPPER(a[j]) && (b[currB] != TOUPPER(a[j])))
            {
                j = currA;
                currA = -1;
                currB = 0;
                continue;
            }
            
            if((b[currB] == TOUPPER(a[j]))
            {
                currB ++;
                if(b[currB] == '\0')
                {
                    if (j >= lA)
                    {
                        done = 1;
                        break;
                    }
                    else
                    {
                        j = currA;
                        currA = -1;
                        currB = 0;
                        continue;
                    }
                }
            }
                   
        }
    }
    
}