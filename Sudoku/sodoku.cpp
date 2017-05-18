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
			cout << *iIt << " "; 
		}
		cout << endl;
	}
}

void removeFromRow(int row,int val, int size, vector <vector <vector <int> > > possibilities)
{
	int i,j;
	for(i=0;i<size;i++)
	{
		possibilities[row][i][val] = 0;
	}	
}

void removeFromCol(int col,int val, int size, vector <vector <vector <int> > >& possibilities)
{
	int i,j;
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
		for (j=colStart;i<colStart + dim;j++)
		{
			possibilities[i][j][val] = 0;
		}
	}
}

int isSingle(vector <int> vec)
{
	int pos,finPos = 0;
	uint8_t count = 0;
	for (pos = 0; pos < vec.size(); pos++)
	{
		if(vec[pos] = 1)
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
	vector <int> setOfAll;
	int size = dim * dim;
	int i,j,k,blocksLeft,prevBlocksLeft;
	int val;
	possibilities.resize(size);
	for(i=0;i<size;i++)
	{
		possibilities[i].resize(size);
		setOfAll[i] = 1;
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
					sudoku [i][j] = val; // TODO
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

	cout << "The unsolved sudoku" << endl << endl ;

	display(sudoku);
	solve (sudoku,dim);

	display(sudoku);	
}
