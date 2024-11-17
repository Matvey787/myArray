#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

// todo fix relative path
#include "../h_files/structs.h"
//#include "structs.h"
#include "../h_files/constants.h"
#include "../h_files/writeData.h"
#include "../h_files/writeHtmlFile.h"
#include "../h_files/insDelElem.h"

const size_t c_stNumOfElem = 7;

void dtor(array_t* data);
void ctor(array_t* data);

int main(){
    int numOfCall = 0;
    system("rm -rf trees");
    system("mkdir -p trees");
    // TODO ctor dtor
    array_t data = {0}; // TODO rename array_t
    ctor(&data);

    /*for (size_t i = 0; i < data.length; i++){

        data.array[i].value = (i < c_stNumOfElem) ? (double)(i * 10) : c_poisonNum;
        data.array[i].next = i < (c_arrSize - 1) ? i + 1 : 0;
        data.array[i].prev = (i > 0) ? i - 1 : c_stNumOfElem - 1;
        
        if (i == c_stNumOfElem - 1){
            data.array[i].next = 0;
        }
            

    }*/
    writeData(&data);
    getchar();
    insElem(&data, 0, 11, "tree.dot", &numOfCall);

    writeData(&data);

    insElem(&data, 1, 11, "tree.dot", &numOfCall);
    writeData(&data);
    delElem(&data, 1, "tree.dot", &numOfCall);
    writeData(&data);
    // insElem(&data, 6, 66, "tree.dot", &numOfCall);
    // insElem(&data, 7, 88, "tree.dot", &numOfCall);
    // insElem(&data, 8, 99, "tree.dot", &numOfCall);
    // insElem(&data, 9, 111, "tree.dot", &numOfCall);

    dtor(&data);
    return 0;
}

void ctor(array_t* data){
    assert(data != nullptr);
    data->array = (elem_t*)calloc(c_arrSize, sizeof(elem_t));

    if (data->array == nullptr){
        printf("couldn't allocate memory");
        return;
    }
    data->freeCell = 1;
    data->length = c_arrSize;

    data->array[0].value = c_poisonNum;
    (data->array)[0].next = 0;
    (data->array)[0].prev = 0;

    for (size_t i = 1; i < data->length; i++){
        (data->array)[i].value = c_poisonNum;
        (data->array)[i].next = (i + 1 == data->length) ? 0 : i + 1;
        (data->array)[i].prev = i - 1;
    }

    data->head = 0;
    data->tail = INT_MAX;
    data->fileName =  "tree.dot";
    data->numOfCallFunc = 0;

}

void dtor(array_t* data){
    assert(data != nullptr);
    assert(data->array != nullptr);

    free(data->array);
    data->array = nullptr;
    data->freeCell = 1;
    data->head = 0;
    data->tail = INT_MAX;
    data->length = c_arrSize;
}