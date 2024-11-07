#ifndef STRUCTS
#define STRUCTS
#include <stdio.h>
#include "../workWithStack/h_files/stackConstructor.h"

struct elem_t
{
    double value;
    size_t next;
    size_t prev;
};

struct data_t
{
    elem_t* array;
    stack_t* freeCells;
    size_t length;
    size_t usedCells;
    size_t head;
    size_t tail;
};

#endif