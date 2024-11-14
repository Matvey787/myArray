#ifndef STRUCTS
#define STRUCTS
#include <stdio.h>

struct elem_t
{
    double value;
    size_t next;
    size_t prev;
};

struct data_t
{
    elem_t* array;
    size_t length;
    size_t freeCell;
    size_t usedCells;
    size_t head;
    size_t tail;
};

#endif