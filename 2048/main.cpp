#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>

using namespace std;


void display(short int  * a)
{
	unsigned char i,j;

	//system("clear");

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if (a[i * 4 +j] == -1)
				cout << " ";
			else
				cout << (int)a[i * 4 +j] ;
			cout << " | ";
		}
		cout << endl;
	}
	cout << endl;
}

void updateRight(short int  * a)
{
	char i,j,initPos = -1;


	for(i=0;i<4;i++)
	{
		initPos = -1;
		for(j=0;j<4;j++)
		{
			if (a[i * 4 +j] != -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
				if(a[i * 4 +j] == a[i * 4 +initPos])
				{
					a[i * 4 +initPos] = -1;
					a[i * 4 +j] += a[i * 4 +j];
					initPos = -1;
					continue;
				}
				initPos = j;
			}
		}
	}


	for (i=0;i<4;i++)
	{
		initPos = -1;
		for(j=3;j>=0;j--)
		{
			if(a[i * 4 +j] == -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
			}
			if(initPos == -1)
			{
				continue;
			}
			if (a[i * 4 + j] != -1)
			{
				a[i * 4 +initPos] = a[i * 4 +j];
				a[i * 4 +j] = -1;
				initPos --;
			}
		}
	}
}

void updateDown(short int  * a)
{
	char i,j,initPos = -1;


	for(i=0;i<4;i++)
	{
		initPos = -1;
		for(j=0;j<4;j++)
		{
			if (a[j * 4 +i] != -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
				if(a[j * 4 +i] == a[initPos * 4 +i])
				{
					a[initPos * 4 +i] = -1;
					a[j * 4 +i] += a[j * 4 +i];
					initPos = -1;
					continue;
				}
				initPos = j;
			}
		}
	}


	for (i=0;i<4;i++)
	{
		initPos = -1;
		for(j=3;j>=0;j--)
		{
			if(a[j * 4 +i] == -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
			}
			if(initPos == -1)
			{
				continue;
			}
			if (a[j * 4 + i] != -1)
			{
				a[initPos * 4 +i] = a[j * 4 +i];
				a[j * 4 +i] = -1;
				initPos --;
			}
		}
	}
}

void updateUp(short int  * a)
{
	char i,j,initPos = -1;


	for(i=0;i<4;i++)
	{
		initPos = -1;
		for(j=3;j>=0;j--)
		{
			if (a[j * 4 +i] != -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
				if(a[j * 4 +i] == a[initPos * 4 +i])
				{
					a[initPos * 4 +i] = -1;
					a[j * 4 +i] += a[j * 4 +i];
					initPos = -1;
					continue;
				}
				initPos = j;
			}
		}
	}


	for (i=0;i<4;i++)
	{
		initPos = -1;
		for(j=0;j<4;j++)
		{
			if(a[j * 4 +i] == -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
			}
			if(initPos == -1)
			{
				continue;
			}
			if (a[j * 4 + i] != -1)
			{
				a[initPos * 4 +i] = a[j * 4 +i];
				a[j * 4 +i] = -1;
				initPos ++;
			}
		}
	}
}

void updateLeft(short int  * a)
{
	char i,j,initPos = -1;


	for(i=0;i<4;i++)
	{
		initPos = -1;
		for(j=3;j>=0;j--)
		{
			if (a[i * 4 +j] != -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
				if(a[i * 4 +j] == a[i * 4 +initPos])
				{
					a[i * 4 +initPos] = -1;
					a[i * 4 +j] += a[i * 4 +j];
					initPos = -1;
					continue;
				}
				initPos = j;
			}
		}
	}


	for (i=0;i<4;i++)
	{
		initPos = -1;
		for(j=0;j<4;j++)
		{
			if(a[i * 4 +j] == -1)
			{
				if(initPos == -1)
				{
					initPos = j;
					continue;
				}
			}
			if(initPos == -1)
			{
				continue;
			}
			if (a[i * 4 + j] != -1)
			{
				a[i * 4 +initPos] = a[i * 4 +j];
				a[i * 4 +j] = -1;
				initPos ++;
			}
		}
	}
}

typedef struct __pair
{
	unsigned char a,b;
}Pair;

int addNewElement(short int * a)
{
	unsigned char i,j;

	Pair temp;
	vector <Pair> l;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i*4 + j] == -1)
			{
				temp.a = i;
				temp.b = j;
				l.push_back(temp);
			}

			if(a[i*4 + j] == 64)
			{
				return 1;
			}
		}
	}

	if (l.size() == 0)
	{
		return -1;
	}

	i = rand () % l.size();
	j = (rand () % 2) + 1;

	a[(l[i].a * 4) + l[i].b] = j * 2;

	return 0;
}



int main()
{
	int retVal;
	char c;
	short int matrix [4][4] = {
		{-1,-1,-1,-1},
		{-1,-1,-1,-1},
		{-1,-1,-1,-1},
		{-1,-1,-1,-1}
	};

	addNewElement((short int *) matrix);
	addNewElement((short int *) matrix);
	display ((short int *) matrix);

	while(1)
	{
		c = getchar();
		getchar();
		switch(c)
		{
			case 'w':
				updateUp((short int *)matrix);
				break;

			case 's':
				updateDown((short int *)matrix);
				break;

			case 'a':
				updateLeft((short int *)matrix);
				break;

			case 'd':
				updateRight((short int *)matrix);
				break;
		}

		retVal = addNewElement((short int *)matrix);
		switch (retVal)
		{
			case -1:
				cout << "game over";
				break;

			case 1:
				cout << "You win";
				break;
		}
		display ((short int *)matrix);
	}

}
