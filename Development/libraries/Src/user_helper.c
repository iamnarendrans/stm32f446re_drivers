/*
 * user_helper.c
 *
 *  Created on: Apr 15, 2024
 *      Author: iamna
 */

#include "stdio.h"
#include "user_helper.h"

size_t h_strlen(const char* str) {
    size_t len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}
