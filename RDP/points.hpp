#ifndef _POINTS_HPP_
	#define _POINTS_HPP_

#include <stdint.h>

typedef float preUnit;
class points
{
	private:
		preUnit x;
		preUnit y;

	public:
		points () {}
		points(preUnit xPos, preUnit yPos);
		preUnit getX();
		preUnit getY();
		preUnit perpDist(points start, points end);
		void getPoints(preUnit * const x, preUnit * const y );
		void display ();
		void operator= (const points& p);
};
#endif