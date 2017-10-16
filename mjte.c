#include <stdio.h>
#include <string.h>

#define SIZE  100
int main()
{
  int len = 0;
  int i=0,j=0;

  int array[SIZE] = {0};
  int cost[SIZE] = {0};
  scanf ("%d",&len);

  for (i = 0;i< len;i++)
  {
    scanf("%d",&array[i]);
    cost[i] = 1000;
  }
  cost[len-1] = 0;

  for (j=len-1;j>=0;j--)
  {
    for (i=1;((i+j<len) && (i<=array[j]));i++)
    {
      if(cost[j] > cost[i+j] + 1)
      {
        cost[j] = cost[i+j] + 1;
      }
    }
  }

  printf("%d\n",cost[0]);
}
