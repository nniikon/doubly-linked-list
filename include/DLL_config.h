#ifndef DLL_CONFIG_H
#define DLL_CONFIG_H

const unsigned int DLL_DEFAULT_CAPACITY = 8;

const float DLL_CAPACITY_MULTIPLIER = 2.0f;

const int DLL_PREV_POISON = -666;
const int DLL_DATA_POISON = __INT_MAX__;

typedef int elem_t;
#define ELEM_FORMAT "%d"

#endif