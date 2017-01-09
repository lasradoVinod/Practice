#include <iostream>
#include "points.hpp"
#include "RDP.hpp"

float pointsInCurve [5][2] = 
{
	{0,1},
	{-0.1,0.5},
	{0,0},
	{0.5,0.3},
	{1,0}
};


int main()
{
	pointList ResultList;
	points p[5]; 
	unsigned char ind;

	for(ind = 0;ind < 5;ind++)
	{
		p[ind] = *(new points(pointsInCurve[ind][0],pointsInCurve[ind][1]));
	}
	
	ResultList = RDPFunction(5,p,0.2);
	
	std::list<points>::iterator iterator;	
	for (iterator = ResultList.begin(); iterator != ResultList.end(); ++iterator) {
		(*iterator).display();
	}
	return 0;
}