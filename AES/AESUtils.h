#include <stdint.h>

typedef enum __RotDir
{
	enLeft,
	enRight
}RotDir;

int rotateRow(uint8_t * const a, uint8_t rNum, RotDir dir);