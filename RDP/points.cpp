#include <iostream>
#include "points.hpp"
#include <cmath>

points::points(preUnit xPos, preUnit yPos)
{
	x = xPos;
	y = yPos;
}


preUnit points::getX()
{
	return x;
}


preUnit points::getY()
{
	return y;
}


void points::getPoints(preUnit * const xPos, preUnit * const yPos )
{
	*xPos = x;
	*yPos = y;
}


preUnit points::perpDist(points start, points end)
{

	preUnit A = x - start.getX();
	preUnit B = y - start.getY();    // A and B are the vector representation of start and current point
	preUnit C = end.getX() - start.getX();
	preUnit D = end.getY() - start.getY();		// C and D are the vector representation of start and end point

	preUnit dot = A * C + B * D;   // dot product to find exactly where the point on the line segment lies
	preUnit len_sq = C * C + D * D; // length of segment squared
	preUnit param = -1;

	if (len_sq != 0) //in case of 0 length line
		param = dot / len_sq;   // This is the portion of the segment at which the projection of the point is on the line
	else
		return -1;

	preUnit xx, yy;

	// if param is less than 0, it means that the projection is on the left side of line so the shortest dist is between start and point
	if (param < 0) {
		xx = start.getX();
		yy = start.getY();
	}
	// on the other side
	else if (param > 1) {
		xx = end.getX();
		yy = end.getY();
	}
	/*Where excatly on the line*/
	else {
		xx = start.getX() + param * C;
		yy = start.getY() + param * D;
	}

	preUnit dx = x - xx;
	preUnit dy = y - yy;    //dx and dy is a vector representing the shortest line.
	return std::sqrt(dx * dx + dy * dy);
}

void points::operator=(const points& p)
{
	this->x = p.x;
	this->y = p.y;
}

void points::display ()
{
	std::cout << "x: " << x << " y: " << y << std::endl;
}