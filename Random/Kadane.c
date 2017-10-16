#include <stdio.h>

#define MAX_N       1001
int main()
{
	int maxi,maxj;
	int max = –2147483648;
	int Array[MAX_N][MAX_N] = {{0}};
	int T, N;
	int Data[MAX_N] ={0};

	scanf("%d",&T);

	for (int i=0;i<T;i++)
	{
		max = –2147483648;
		scanf("%d",&N);
		for (int j=0;j<N;j++)
		{
			scanf("%d",&Data[j]);
			Array[0][j] = Data[j];
			if (Data[j] > max)
			{
				max = Data[j];
				maxi = 0;
				maxj = j;
			}
		}

		for(int j=1;j<N;j++)
		{
			for (k=0;k<N;k++)
			{
				Array[j][k] = Data[k] + Array[j-1][k+1];
				if(Array[j][k] > max)
				{
					max = Array[j][k];
					maxi = j;
					maxj = k;		
				}
			}
		}

		printf("%d\n",max);
	}     
}