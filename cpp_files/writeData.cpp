#include <stdio.h>
#include <stdlib.h>
#include "../h_files/structs.h"
#include "../h_files/writeData.h"
#include "../workWithStack/h_files/stackPushPop.h"
#include "../h_files/constants.h"

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)

void writeData(data_t* data, const char* fileName, int numOfCall){
    FILE* wFile = fopen(fileName, "wb");
    fprintf(wFile, "digraph\n{\nrankdir=LR;\n");
    data->head = 0;
    data->tail = 100;
    size_t freeCell = (size_t)stackPop(data->freeCells);

    for (size_t i = 0; i < data->length; i++){
        printf("%lu %lu %lg\n", data->tail, i+1, data->array[i].value);
        if ((data->array[i].value - c_poisonNum) > c_compareZero)
            {
                if (data->array[i].next == 0)
                data->head = MAX(data->head, i);

                if (data->array[i].prev == 0)
                    data->tail = MIN(data->tail, i);
            }
        fprintf(wFile, "node00%lu [shape=Mrecord label= \" 00%lu | data = %lg | <n%lu_n> next = %lu | <n%lu_p> prev = %lu \" ];\n",
         i, i, data->array[i].value, i, data->array[i].next, i, data->array[i].prev);

        //printf("%lg %lu %lu\n", data->array[i].value, data->array[i].next, data->array[i].prev); 
    }
    fprintf(wFile, "\n");
    fprintf(wFile, "info [shape=Mrecord label= \" Info | freeCell: %lu | <info_h> HEAD: %lu | <info_t> TAIL: %lu \" ];\n",
            freeCell, data->head, data->tail);
    stackPush(data->freeCells, (double)freeCell);
    fprintf(wFile, "info:<info_h> -> node00%lu [ color = green; ]\n", data->head);
    fprintf(wFile, "info:<info_t> -> node00%lu [ color = green; ]\n", data->tail);

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length - 1; i++){
        fprintf(wFile, "node00%lu -> node00%lu [ weight = 1000; color = white; ]\n", i, i+1);
    }

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length; i++){
        if ((data->array[i].value - c_poisonNum) > c_compareZero)
            fprintf(wFile, "node00%lu:<n%lu_p> -> node00%lu:<n%lu_p> [ color = blue; ]\n", i, i, data->array[i].prev, data->array[i].prev);
    }

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length; i++){
        if ((data->array[i].value - c_poisonNum) > c_compareZero)
            fprintf(wFile, "node00%lu:<n%lu_n> -> node00%lu:<n%lu_n> [ color = red; ]\n", i, i, data->array[i].next, data->array[i].next);
    }

    fprintf(wFile, "}");
    printf("-----\n");
    fclose(wFile);

    char pngFile[100];
    const char* startOfName = "dot tree.dot -Tpng -o trees/tree";
    sprintf(pngFile, "%s%d.png", startOfName, numOfCall++);
    system(pngFile);
}