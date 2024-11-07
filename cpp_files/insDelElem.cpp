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

    // size_t addCell = freeCell - freeCell * index / (data->head);
    //printf("%d %d\n", index, data->usedCells);
    
    if (index < 0){
        printf("problem: index < 0\n");
        return;
    } else if ((index - data->usedCells) > 1) {
        printf("problem: index higer then used cells more then 1");
        return;
    }

    if (index >= data->usedCells){
        printf("-------------------\n");
        data->array[freeCell].next = 0;
        data->array[freeCell].prev = data->head;
        data->array[freeCell].value = value;

        data->array[data->head].next = freeCell;
        data->array[0].prev = freeCell;
        data->usedCells += 1;
        return;
    }
    data->array[freeCell].next = index;
    data->array[freeCell].prev = data->array[index].prev;
    data->array[freeCell].value = value;
    data->array[data->array[index].prev].next = freeCell;
    data->array[index].prev = freeCell;
    
}

void delElem(data_t* data, size_t index){
    assert(data != nullptr);

    data->array[index].value = c_poisonNum;
    data->array[data->array[index].prev].next = data->array[index].next;    
    data->array[data->array[index].next].prev = data->array[index].prev;
    stackPush(data->freeCells, (double)index);
}
