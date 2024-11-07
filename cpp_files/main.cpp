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

    data_t data = {(elem_t*)calloc(c_arrSize, sizeof(elem_t)), &freeCells, c_arrSize, numOfElem, 0, 100};
    //printf("%d", data.usedCells);
    for (size_t i = 0; i < data.length; i++){

        data.array[i].value = (i < numOfElem) ? (double)(i * 10) : c_poisonNum;
        data.array[i].next = i < (numOfElem-1) ? i + 1 : 0;
        data.array[i].prev = (i > 0) ? i - 1 : numOfElem - 1;
        
        if (i >= numOfElem)
            stackPush(data.freeCells, (double)i);
    }

    writeData(&data, "tree.dot", numOfCall++);
    insElem(&data, 7, 20.5);
    writeData(&data, "tree.dot", numOfCall++);
    insElem(&data, 8, 20.5);
    writeData(&data, "tree.dot", numOfCall++);

    writeHtmlFile("trees.html", numOfCall);

    stackDestroy(data.freeCells);
    free(data.array);
    return 0;
}
