#ifndef INSDELELEM
#define INSDELELEM
#include "structs.h"

void insElem(data_t* data, size_t index, double value, const char* fileName, int* numOfCall);
void delElem(data_t* data, size_t index, const char* fileName, int* numOfCall);

#endif