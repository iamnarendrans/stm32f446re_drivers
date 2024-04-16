/*
 * user_math.c
 *
 *  Created on: Apr 16, 2024
 *      Author: iamna
 */

#include "user_math.h"

uint32_t MAP(uint32_t u32_in, uint32_t u32_inMin, uint32_t u32_inMax, uint32_t u32_outMin, uint32_t u32_outMax)
{
	return ((((u32_in - u32_inMin)*(u32_outMax - u32_outMin))/(u32_inMax - u32_inMin)) + u32_outMin);
}

uint32_t Constrain(uint32_t u32_in, uint32_t u32_inMin, uint32_t u32_inMax)
{
	if(u32_in < u32_inMin)
	{
		return u32_inMin;
	}
	else if (u32_in > u32_inMax)
	{
		return u32_inMax;
	}
	else
	{
		return u32_in;
	}
}

MATH_DataType MIN(MATH_DataType* in_Arr, uint32_t u32_len)
{
	uint32_t i = 0;
	MATH_DataType MIN = 0;

	for(i=0; i<u32_len; i++)
	{
		if(in_Arr[i] < MIN)
		{
			MIN = in_Arr[i];
		}
	}
	return MIN;
}

MATH_DataType MAX(MATH_DataType* in_Arr, uint32_t u32_len)
{
	uint32_t i = 0;
	MATH_DataType MAX = 0;

	for(i=0; i<u32_len; i++)
	{
		if(in_Arr[i] > MAX)
		{
			MAX = in_Arr[i];
		}
	}
	return MAX;
}
