#include <stdio.h>
#include <string.h>

#define SIZE	100
int main()
{
	int cost[26] = {0};
	char array[SIZE+1] = {0};
	
	scanf("%s",array);
	int len = strlen(array);
	int maxLen = 0;
	int currLen = 0;
	int start = -1;
	for (int i=0; i<len; i++)
	{
		if (cost[array[i]-'A'] <= start)
		{
			cost[array[i] - 'A'] = i;
			currLen += 1;
			continue;
		}
		else
		{
			start = i;
			if(currLen > maxLen)
			{
				maxLen = currLen;
			}
			currLen = 0;
		}
	}
	printf("%d\n",maxLen);
}