#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../h_files/insDelElem.h"
#include "../workWithStack/h_files/stackPushPop.h"
#include "../h_files/constants.h"

void insElem(data_t* data, size_t index, double value){
    assert(data != nullptr);
    assert(data->freeCells != nullptr);
    size_t freeCell = (size_t)stackPop(data->freeCells);

    data->array[freeCell].next = index;
    data->array[freeCell].prev = data->array[index].prev;
    data->array[freeCell].value = value;
    data->array[data->array[index].prev].next = freeCell;
    data->array[index].prev = freeCell;
    
}

void delElem(data_t* data, size_t index){
    assert(data != nullptr);
    data->array[index].value = c_poisonNum;
    if (data->array[index].prev > 0)
        data->array[data->array[index].prev].next = data->array[index].next;
        
    data->array[data->array[index].next].prev = data->array[index].prev;
    stackPush(data->freeCells, (double)index);
}
