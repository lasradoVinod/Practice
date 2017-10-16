#include <stdio.h>

#define SIZE 		100
#define MAX(a,b)	(a>b?a:b)
int main()
{
	int i,j,len;

	int arr[SIZE] = {0};
	int lis[SIZE] = {0};
	scanf ("%d",&len);

	for (i=0;i<len;i++)
	{
		scanf("%d",&arr[i]);
		lis[i] = 1;
	}

	int maxLen = 1;
	for (i=0;i<len;i++)
	{
		for (j = i+1; j< len; j++)
		{
			if (arr[j] > arr[i])
			{
				lis[j] = MAX(lis[j],lis[i]+1);
				if (lis[j] > maxLen)
				{
					maxLen = lis[j];
				}
			}
		}
	}

	printf("%d\n",maxLen);
}