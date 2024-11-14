#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../h_files/structs.h"
#include "../h_files/writeData.h"
#include "../h_files/constants.h"

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)

void writeData(data_t* data, const char* fileName, int numOfCall){
    //printf("call %d\n", numOfCall);
    assert(data != nullptr);
    assert(fileName != nullptr);
    
    FILE* wFile = fopen(fileName, "wb");

    if (wFile == nullptr)
    {
        printf("couldn't open file\n");
        return;
    }

    fprintf(wFile, "digraph\n{ \n\
                    rankdir=LR; \n\
                    overlap=false; \n\
                    splines=true; \n\
                    nodesep=0.75; \n\
                    ranksep=0.5;\n");
    data->head = 0;
    data->tail = 100;
    //printf("----%lu----\n", data->length);
    for (size_t i = 0; i < data->length; i++){
        //printf("%lu %lu %lg\n", data->tail, i+1, data->array[i].value);
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
            data->freeCell, data->head, data->tail);
    fprintf(wFile, "info:<info_h> -> node00%lu [ color = green; ]\n", data->head);
    fprintf(wFile, "info:<info_t> -> node00%lu [ color = green; ]\n", data->tail);

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length - 1; i++){
        
        fprintf(wFile, "node00%lu -> node00%lu [ weight = 1; color = white; ]\n", i, i+1);
    }

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length; i++){
        if ((data->array[i].value - c_poisonNum) > c_compareZero)
            fprintf(wFile, "node00%lu:<n%lu_p>:w -> node00%lu:<n%lu_p>:s [ color = blue; minlen=2; constraint=false; ]\n", i, i, data->array[i].prev, data->array[i].prev);
    }

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length; i++){
        if ((data->array[i].value - c_poisonNum) > c_compareZero)
            fprintf(wFile, "node00%lu:<n%lu_n>:e -> node00%lu:<n%lu_n>:w [ color = red; minlen=2; constraint=false; ]\n", i, i, data->array[i].next, data->array[i].next);
        else if (data->array[i].next != 0)
         fprintf(wFile, "node00%lu:<n%lu_n>:e -> node00%lu:<n%lu_n>:w [ color = orange; minlen=2; constraint=false; ]\n", i, i, data->array[i].next, data->array[i].next);
    }

    fprintf(wFile, "}\n");
    //printf("-----\n");
    fclose(wFile);

    char pngFile[200] = {0};
    const char* startOfName = "dot tree.dot -Tpng -o trees/tree";
    sprintf(pngFile, "%s%d.png", startOfName, numOfCall++);
    system(pngFile);
}