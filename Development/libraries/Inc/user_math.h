/*
 * user_math.h
 *
 *  Created on: Apr 16, 2024
 *      Author: iamna
 */

#ifndef INC_USER_MATH_H_
#define INC_USER_MATH_H_

#include <stdint.h>

typedef uint32_t MATH_DataType;

uint32_t MAP(uint32_t u32_in, uint32_t u32_inMin, uint32_t u32_inMax, uint32_t u32_outMin, uint32_t u32_outMax);

uint32_t Constrain(uint32_t u32_in, uint32_t u32_inMin, uint32_t u32_inMax);

MATH_DataType MIN(MATH_DataType* in_Arr, uint32_t u32_len);

MATH_DataType MAX(MATH_DataType* in_Arr, uint32_t u32_len);

#endif /* INC_USER_MATH_H_ */
