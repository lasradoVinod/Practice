#ifndef _RDP_HPP_
	#define _RDP_HPP_
#include <iostream>
#include <list>
#include <stdint.h>
#include "points.hpp"
#include "RDP.hpp"

typedef std::list <points> pointList;

pointList RDPFunction(uint32_t numPts, points p[], float epsilon);

#endif