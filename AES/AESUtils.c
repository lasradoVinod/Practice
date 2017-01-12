#include <stdio.h>
#include <stdint.h>
#include "AESUtils.h"
#include "lookUp.h"


int rotateRow(uint8_t * const a, uint8_t rNum, RotDir dir)
{
	uint8_t iter,temp[4];
	if(rNum > 4)
		return -1;

	if(dir == enRight)
	{
		if(rNum != 0)
		{
			rNum = 4 - rNum;
		}
	}
	for(iter = 0;iter < 4 ;iter ++)
	{
		temp[iter] = a[iter];
	}
	
	for(iter = 0;iter < 4 ;iter ++)
	{
		a[iter] = temp[(iter + rNum )% 4];
	}	
	return 0;
}

uint8_t byteSub(uint8_t byteVal)
{
	return sBox[(byteVal>>4) & 0x0F][byteVal & 0x0F];
}

void convert (uint8_t state[4][4], uint8_t input[])
{
	uint8_t ind, innerInd, count = 0;
	for(ind = 0; ind < 4 ; ind ++)
	{
		for(innerInd=0;innerInd<4;innerInd++)
		{
			state[innerInd][ind] = input[count];
			count++;
		}
	}
}

int L(uint8_t byteVal)
{
	return LTable[(byteVal>>4) & 0x0F][byteVal & 0x0F];
}

int E(uint8_t byteVal)
{
	return ETable[(byteVal>>4) & 0x0F][byteVal & 0x0F];
}

void performMul(uint8_t state[4][4])
{
	int tempVal;
	uint8_t temp;
	uint8_t outputState [4][4] = {{0}};
	uint8_t iter,innerIter, count = 0;
	
	for(count = 0; count < 4; count++)
	{
		for(iter = 0; iter < 4; iter ++)
		{
			temp = 0;
			for(innerIter=0; innerIter<4 ; innerIter ++)
			{

				tempVal = (L(state[innerIter][count]) + L(MulMatrix[iter][innerIter]));
				tempVal = tempVal < 0xFF? tempVal:(tempVal - 0xFF);
				tempVal = E((uint8_t) tempVal);

				temp ^= tempVal;
			
			}
			outputState[iter][count] = temp;

		}
	}

	for(iter = 0; iter < 4; iter ++)
	{
		for(innerIter=0; innerIter<4 ; innerIter ++)
		{
			state[iter][innerIter] = outputState[iter][innerIter] ;
		}
	}
}

uint8_t RCon(uint8_t round, uint8_t keySize,uint8_t index)
{
	return rCon[index][(round/(keySize/4))-1];
}

void dislay(uint8_t * a)
{
	uint8_t iter;
	for (iter=0;iter<4;iter++)
	{
		printf("%x ",a[iter]);
	}
}

void keyGeneration(void* a, uint8_t inpKey[16], KeySize keySize)
{
	uint8_t (*roundKey)[4][(4*(keyMap[keySize] + 1))] = (uint8_t (*) [4][(4*(keyMap[keySize] + 1))])a;
	uint8_t ind,iInd,count = 0;
	uint8_t col[4] = {0};
	for(ind=0;ind<4;ind++)
	{
		for(iInd=0;iInd<4;iInd++)
		{
			(*roundKey)[iInd][ind] = inpKey[count++];
		}
	}
	
	for(ind=4;ind<(4*(keyMap[keySize] + 1));ind++)
	{
		for(iInd=0;iInd<4;iInd++)
		{
			col[iInd] = (*roundKey)[iInd][ind-1];
		}
		
		if((ind %4) == 0)
		{
			rotateRow(col,1,enLeft);

			for(iInd=0;iInd<4;iInd++)
			{
				col[iInd] = byteSub(col[iInd]) ^ RCon(ind,keyActSize[keySize],iInd);
			}
		}
		
		printf("\nFinal column: ");
		
		for(iInd=0;iInd<4;iInd++)
		{
			col[iInd] ^= (*roundKey)[iInd][ind-4];
			(*roundKey)[iInd][ind] = col[iInd];
		}
	}
}


int main()
{
	uint8_t key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	uint8_t state[4][4] = {{0}};
	uint8_t input[] = {0xD4,0xBF,0x5D,0x30,5,6,7,8,9,10,11,12,13,14,15,16};
	uint8_t iter,innerIter, count = 0;
	uint8_t roundKey[4][44] = {{0}};
	
    keyGeneration(roundKey,key,enKeySize_128);
	
	for(iter=0;iter<4;iter++)
	{
		for(innerIter=0;innerIter<44;innerIter++)
		{
			printf("%d",roundKey[innerIter][iter]);
		}
	}
	
	return 0;
}

