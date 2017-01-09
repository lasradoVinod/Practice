#include <iostream>
#include <list>
#include <iterator>
#include <stdint.h>
#include "points.hpp"
#include "RDP.hpp"

pointList RDPFunction(uint32_t numPts, points p[], float epsilon)
{
	pointList recResults1,recResults2,ResultList;
	uint32_t ind;
    float dmax = 0;
    uint32_t index = 0;
    float d = 0;
	
	if(numPts < 2)
	{
		ResultList.push_back(p[0]);
		return ResultList;
	}
	
    for (ind = 1; ind < numPts - 1; ind++  ){
        d = p[ind].perpDist(p[0],p[numPts-1]); 
        if ( d > dmax ) {
            index = ind;
            dmax = d;
        }
    }
    // If max distance is greater than epsilon, recursively simplify
    if ( dmax > epsilon ) {
        // Recursive call
        recResults1 = RDPFunction(index + 1,&p[0], epsilon);
        recResults2 = RDPFunction((numPts - index),&p[index], epsilon);

        // Build the result list
        //ResultList[] = {recResults1[1...length(recResults1)-1], recResults2[1...length(recResults2)]}
		std::list<points>::const_iterator iterator;
		
		for (iterator = recResults1.begin(); iterator != recResults1.end(); ++iterator) {
			ResultList.push_back(*iterator);
		}
		
		for (iterator = recResults2.begin(); iterator != recResults2.end(); ++iterator) {
			if(iterator != recResults2.begin())
			{
				ResultList.push_back(*iterator);
			}
		}
		
    } else {
        ResultList.push_back(p[0]);
		ResultList.push_back(p[numPts-1]);
    }
    // Return the result
    return ResultList;
}