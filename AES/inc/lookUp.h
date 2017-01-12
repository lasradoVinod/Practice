#ifndef _LOOK_UP_
	#define _LOOK_UP_
	
#include <stdint.h>
typedef enum __KeySize
{
	enKeySize_128 = 0,
	enKeySize_192,
	enKeySize_256
}KeySize;

extern uint8_t sBox [16][16];

extern uint8_t invsBox [16][16];

extern uint8_t rCon[4][15];

extern uint8_t LTable [16][16];

extern uint8_t ETable [16][16];

extern uint8_t MulMatrix[4][4];

extern uint8_t keyMap[3];

extern uint8_t keyActSize[3];

#endif