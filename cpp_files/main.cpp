#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../h_files/structs.h"
#include "../h_files/constants.h"
#include "../h_files/writeData.h"
#include "../h_files/writeHtmlFile.h"
#include "../h_files/insDelElem.h"

const size_t c_stNumOfElem = 7;

void dtor(data_t* data);
void ctor(data_t* data);

int main(){
    int numOfCall = 0;
    system("rm -rf trees");
    system("mkdir -p trees");
    // TODO ctor dtor
    data_t data = {0}; // TODO rename data_t
    ctor(&data);

    //printf("%d", data.usedCells);
    for (size_t i = 0; i < data.length; i++){

        data.array[i].value = (i < c_stNumOfElem) ? (double)(i * 10) : c_poisonNum;
        data.array[i].next = i < (c_arrSize - 1) ? i + 1 : 0;
        data.array[i].prev = (i > 0) ? i - 1 : c_stNumOfElem - 1;
        
        if (i == c_stNumOfElem - 1){
            data.array[i].next = 0;
        }
            

    }

    writeData(&data, "tree.dot", numOfCall);

    insElem(&data, 6, 66, "tree.dot", &numOfCall);
    insElem(&data, 7, 88, "tree.dot", &numOfCall);
    insElem(&data, 8, 99, "tree.dot", &numOfCall);
    insElem(&data, 9, 111, "tree.dot", &numOfCall);

    delElem(&data, 8, "tree.dot", &numOfCall);

    writeHtmlFile("trees.html", numOfCall);

    dtor(&data);
    return 0;
}

void ctor(data_t* data){
    assert(data != nullptr);
    data->array = (elem_t*)calloc(c_arrSize, sizeof(elem_t));

    if (data->array == nullptr){
        printf("couldn't allocate memory");
        return;
    }
    data->freeCell = c_stNumOfElem;
    data->head = 0;
    data->tail = 100;
    data->length = c_arrSize;
    data->usedCells = c_stNumOfElem;

}

void dtor(data_t* data){
    assert(data != nullptr);
    assert(data->array != nullptr);
    free(data->array);
    data->array = nullptr;
    data->freeCell = c_stNumOfElem;
    data->head = 0;
    data->tail = 100;
    data->length = c_arrSize;
    data->usedCells = c_stNumOfElem;
}