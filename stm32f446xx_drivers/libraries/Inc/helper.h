/*
 * helper.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Narendran Srinivasan
 */

#ifndef SRC_HELPER_H_
#define SRC_HELPER_H_

uint32_t h_strLen(const char *str);

uint32_t h_arrayLen(const void *arr, size_t element_size);

void h_delay(uint32_t delay_in_S);

void hsi_delay(uint32_t delay_in_s);




#endif /* SRC_HELPER_H_ */
