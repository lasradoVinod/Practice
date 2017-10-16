#include <stdio.h>
#include <string.h>

int main()
{
	char a[100], b[100];
	unsigned char c[100][100];
	unsigned char maxLen;
	char *str1, *str2;
	int n,m;
	unsigned int T;

	scanf("%c",&T);

	for (unsigned int k = 0; k< T; k++)
	{
		maxLen = 0;
		scanf ("%d",&n);
		scanf ("%d",&m);
		for (int i = 0; i < n; i++)
		{
			scanf("%c",&a[i]);
		}
		for (int i = 0; i < m; i++)
		{
			scanf("%c",&b[i]);
		}

		if (n == 0 || m == 0)
		{
			printf("0\n");
			continue;
		}		


		for (int i=0;i<=n;i++)
		{
			for (int j=0;j<=m;j++)
			{
				c[i][j] = 0;
			}
		}
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<m;j++)
			{
				if (a[i] == b[j])
				{
					c[i+1][j+1] = c[i][j] + 1;
				}
				else
				{
					c[i+1][j+1] = c[i][j+1] > c[i+1][j] ? c[i][j+1] : c[i+i][j];
				}
				if (maxLen < c[i+1][j+1])
					maxLen = c[i+1][j+1];
			}				
		}

		n = n > m ? n: m;
		printf("%d\n",n-maxLen);
	}
}