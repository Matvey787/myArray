#ifndef STRUCTS
#define STRUCTS
#include <stdio.h>

struct elem_t
{
    double value;
    size_t next;
    size_t prev;
};

// todo list_t 
struct array_t
{
    elem_t* array;
    size_t length;
    size_t freeCell;
    size_t head;
    size_t tail;
    const char* fileName;
    size_t numOfCallFunc;
};

#endif // STRUCTS