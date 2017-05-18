#include <iostream>
#include <stdint.h>

using namespace std;

uint8_t notToFrom (uint8_t frm, uint8_t to)
{
	uint8_t vis[3] = {0};
	uint8_t i;
	vis[frm] = 1;
	vis[to] = 1;

	for(i = 0; i< 3; i++)
	{
		if(vis[i] == 0)
			return i;
	}
}
void solveTower(uint8_t frm, uint8_t to, uint8_t n)
{
	if (n == 1)
	{
		cout << (int)frm << "->" << (int)to << endl;
		return;
	}

	solveTower(frm,notToFrom(frm,to),n-1);
	cout << (int)frm << "->" << (int)to << endl;
	solveTower(notToFrom(frm,to),to,n-1);
}

int main()
{
	solveTower(0,1,4);
}
