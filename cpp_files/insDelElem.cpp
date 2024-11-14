#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../h_files/insDelElem.h"
#include "../h_files/constants.h"
#include "../h_files/writeData.h"

void createMoreCells(data_t* data);

void insElem(data_t* data, size_t index, double value, const char* fileName, int* numOfCall){
    assert(data != nullptr);

    size_t temp = data->freeCell;
    if (temp == 0){
        printf("need more cells\n");
        createMoreCells(data);
        //printf("%lu\n", data->length);
        temp = data->freeCell;
    } else {
        data->freeCell = data->array[data->freeCell].next;
    }
    data->array[temp].next = data->array[index].next;
    data->array[temp].prev = index;
    data->array[temp].value = value;
    data->array[data->array[index].next].prev = temp;
    data->array[index].next = temp;
    
    *numOfCall += 1;
    writeData(data, fileName, *numOfCall);
}

void delElem(data_t* data, size_t index, const char* fileName, int* numOfCall){
    assert(data != nullptr);

    data->array[index].value = c_poisonNum;
    data->array[data->array[index].prev].next = data->array[index].next;    
    data->array[data->array[index].next].prev = data->array[index].prev;
    data->array[index].next = data->freeCell;
    data->freeCell = index;
    data->usedCells -= 1;

    *numOfCall += 1;
    writeData(data, fileName, *numOfCall);
}

void createMoreCells(data_t* data){
    assert(data != nullptr);
    assert(data->array != nullptr);
    size_t newLength = data->length * 2;
    data->array = (elem_t*)realloc(data->array, sizeof(elem_t)*(newLength));
    
    for (size_t i = data->length; i < newLength; i++){
    data->array[i].value = c_poisonNum;
    data->array[i].prev = 0;

    if (i != newLength - 1)
        data->array[i].next = i+1;
    else
        data->array[i].next = 0;
    }
    data->freeCell = data->length;
    data->length = newLength;
    
    return;
}