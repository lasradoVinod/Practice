#include <iostream>
#include <string.h>
#include <stdio.h>
int main()
{
	char num[10001];
	int t;
	int f,b;
	for (int i = 0 ;i < t;i++)
	{ 
		f = b =-1;
		scanf("%s",num);
		for (int j = 0; j < strlen(num) - 1;j++)
		{
			if (num[j] > num[j+1])
			{
				f = j;
				b = j + 1;
			}
			char temp = num[f];
			num[f] = num[b];
			num[b] = temp;
		}
		if (f == -1)
			printf("-1\n");
		else
			printf("%s\n",num );
	}
}