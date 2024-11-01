#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../workWithStack/h_files/stackConstructor.h"
#include "../workWithStack/h_files/stackPushPop.h"
#include "../workWithStack/h_files/stackInitDestroy.h"
#include "../workWithStack/h_files/stackDump.h"

#include "../h_files/structs.h"
#include "../h_files/constants.h"
#include "../h_files/writeData.h"
#include "../h_files/writeHtmlFile.h"
#include "../h_files/insDelElem.h"

int main(){
    int numOfCall = 0;
    size_t numOfElem = 7;
    
    stack_t freeCells;
    MACRO_stackInit(&freeCells);

    data_t data = {(elem_t*)calloc(c_arrSize, sizeof(elem_t)), &freeCells, c_arrSize, 0, 100};

    for (size_t i = 1; i < data.length; i++){
        if (i < numOfElem){
            data.array[i].value = (double)(i * 10);
            data.array[i].next = i == numOfElem-1 ? 0 : i + 1;
            data.array[i].prev = i == 1 ? 0 : i - 1;
        } else {
            data.array[i].value = c_poisonNum;
            stackPush(data.freeCells, (double)i);
        }
    }
    data.array[0].value = -666;
    data.array[0].next = 0;
    data.array[0].prev = 0;

    writeData(&data, "tree.dot", numOfCall++);
    delElem(&data, 1);
    writeData(&data, "tree.dot", numOfCall++);
    insElem(&data, 3, 11.5);
    writeData(&data, "tree.dot", numOfCall++);

    writeHtmlFile("trees.html", numOfCall);

    stackDestroy(data.freeCells);
    free(data.array);
    return 0;
}
