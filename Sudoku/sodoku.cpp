#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdint.h>
#include <stdio.h>

using namespace std;

void display(vector <vector <int> > sudoku)
{
	vector<vector <int> >::const_iterator oIt;
	vector <int>::const_iterator iIt;

	for (oIt= sudoku.begin();oIt != sudoku.end();++oIt)
	{
		for (iIt = oIt->begin(); iIt != oIt->end(); ++iIt)
		{
			if (*iIt == -1 )
				cout << " " << " | ";
 			else
				cout << *iIt << " | ";
		}
		cout << endl;
		for (iIt = oIt->begin(); iIt != oIt->end(); ++iIt)
		{
			cout << "___ ";
		}
		cout << endl;
	}
}

void displayP(vector <vector <vector <int> > > possibilities,int size)
{
	int i,j,k;

	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			cout << i << " " << j << " ";
			for (k=0;k<size;k++)
			{
				    cout << possibilities[i][j][k] << " " ;
			}
			cout << endl;
		}
	}
}
void removeFromRow(int row,int val, int size, vector <vector <vector <int> > >& possibilities)
{
	int i;
	for(i=0;i<size;i++)
	{
		possibilities[row][i][val] = 0;
	}
}

void removeFromCol(int col,int val, int size, vector <vector <vector <int> > >& possibilities)
{
	int i;
	for(i=0;i<size;i++)
	{
		possibilities[i][col][val] = 0;
	}
}

void removeFromGrid(int row,int col,int dim,int val, vector <vector <vector <int> > >& possibilities)
{
	int i,j;
	int rowStart = (row /dim) * dim;
	int colStart = (col /dim) * dim;
	for(i=rowStart;i<rowStart + dim;i++)
	{
		for (j=colStart;j<(colStart + dim);j++)
		{
			possibilities[i][j][val] = 0;
		}
	}
}

int isSingle(vector <int> vec)
{
	unsigned int pos,finPos = 0;
	uint8_t count = 0;
	for (pos = 0; pos < vec.size(); pos++)
	{
		if(vec[pos] == 1)
		{
			if (count == 0)
			{
				count = 1;
				finPos = pos + 1;
			}
			else
			{
				return -1;
			}
		}
	}
	return finPos;
}
int solve(vector <vector <int> >& sudoku,int dim)
{
	vector <vector <vector <int> > > possibilities;
	vector <int> setOfAll,setOfNone;
	int size = dim * dim;
	int i,j,blocksLeft,prevBlocksLeft;
	int val;
	possibilities.resize(size);
	setOfAll.resize(size);
	setOfNone.resize(size);
	for(i=0;i<size;i++)
	{
		possibilities[i].resize(size);
		setOfAll[i] = 1;
		setOfNone[i] = 0;
	}

	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			possibilities[i][j] = setOfAll;
		}
	}

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			if (sudoku[i][j] != -1)
			{
				possibilities[i][j] = setOfNone;
				removeFromRow(i,sudoku [i][j] - 1,size,possibilities);
				removeFromCol(j,sudoku[i][j] - 1,size,possibilities);
				removeFromGrid(i,j,dim,sudoku[i][j] -1,possibilities);
			}
			else
			{
				blocksLeft ++;
			}
		}
	}

	while(blocksLeft != 0)
	{
		prevBlocksLeft = blocksLeft;
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				val = isSingle(possibilities[i][j]);
				if (val > 0)
				{
					sudoku [i][j] = val;
					removeFromRow(i,val - 1,size,possibilities);
					removeFromCol(j,val - 1,size,possibilities);
					removeFromGrid(i,j,dim,val -1,possibilities);
					blocksLeft -- ;
				}
			}
		}
		if(prevBlocksLeft == blocksLeft)
		{
			return -1;
		}
	}

	return 0;
}
int main()
{
	int dim,i,j,k,n,temp,size;
	vector <vector <int> > sudoku;

	setbuf(stdout,NULL);
	//cout << "Enter dimension of sudoku" << endl;
	cin >> dim;

	size = dim * dim;
	sudoku.resize(size);

	for (i = 0;i < size;i++)
	{
		sudoku[i].resize(size);
	}


	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			sudoku[i][j] = -1;
		}
	}

	//cout << "Number of entries" << endl;
	cin >> n;

	for (i = 0;i < n;i++)
	{
		cin >> j >> k >> temp;
		sudoku [j][k] = temp;
	}

	cout << endl << "Input problem" << endl ;
	display(sudoku);

	solve (sudoku,dim);

	cout << endl << "Solution" << endl ;
	display(sudoku);
}

