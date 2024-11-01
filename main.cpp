#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)

struct elem_t
{
    double value;
    size_t next;
    size_t prev;
};

struct data_t
{
    elem_t* array;
    size_t freeCell;
    size_t length;
    size_t head;
    size_t tail;
};

const size_t c_arrSize = 10;
const double c_poisonNum = -666;

void writeData(data_t* data, const char* fileName, int numOfCall);
void insElem(data_t* data, size_t index, double value);
void delElem(data_t* data, size_t index);
void writeHtmlFile(const char* fileName, int numOfFiles);

int main(){
    int numOfCall = 0;
    size_t numOfElem = 7;

    data_t data = {(elem_t*)calloc(c_arrSize, sizeof(elem_t)), numOfElem, c_arrSize, 0, 100};
    for (int i = 1; i < data.length; i++){
        if (i < numOfElem){
            data.array[i].value = i * 10;
            data.array[i].next = i == numOfElem-1 ? 0 : i + 1;
            data.array[i].prev = i == 1 ? 0 : i - 1;
        } else {
            data.array[i].value = c_poisonNum;
        }
        
    }
    data.array[0].value = -666;
    data.array[0].next = 0;
    data.array[0].prev = 0;

    writeData(&data, "tree.dot", numOfCall++);
    insElem(&data, 3, 11.5);
    writeData(&data, "tree.dot", numOfCall++);
    delElem(&data, 1);
    writeData(&data, "tree.dot", numOfCall++);
    delElem(&data, 2);
    writeData(&data, "tree.dot", numOfCall++);
    delElem(&data, 3);
    writeData(&data, "tree.dot", numOfCall++);

    writeHtmlFile("trees.html", numOfCall);
    free(data.array);
    return 0;
}

void writeData(data_t* data, const char* fileName, int numOfCall){
    FILE* wFile = fopen(fileName, "wb");
    fprintf(wFile, "digraph\n{\nrankdir=LR;\n");
    data->head = 0;
    data->tail = 100;
    for (size_t i = 0; i < data->length; i++){
        printf("%d %d %lg\n", data->tail, i+1, data->array[i].value);
        if ((data->array[i].value != c_poisonNum))
            {
                if (data->array[i].next == 0)
                data->head = MAX(data->head, i);

                if (data->array[i].prev > 0)
                    data->tail = MIN(data->tail, data->array[i].prev);
            }
        fprintf(wFile, "node00%ld [shape=Mrecord label= \" 00%ld | data = %lg | <n%ld_n> next = %ld | <n%ld_p> prev = %ld \" ];\n",
         i, i, data->array[i].value, i, data->array[i].next, i, data->array[i].prev);

        //printf("%lg %lu %lu\n", data->array[i].value, data->array[i].next, data->array[i].prev); 
    }
    fprintf(wFile, "\n");
    fprintf(wFile, "info [shape=Mrecord label= \" Info | freeCell: %ld | <info_h> HEAD: %ld | <info_t> TAIL: %ld \" ];\n",
            data->freeCell, data->head, data->tail);
    fprintf(wFile, "info:<info_h> -> node00%ld [ color = green; ]\n", data->head);
    fprintf(wFile, "info:<info_t> -> node00%ld [ color = green; ]\n", data->tail);

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length - 1; i++){
        fprintf(wFile, "node00%ld -> node00%ld [ weight = 1000; color = white; ]\n", i, i+1);
    }

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length; i++){
        if (data->array[i].value != c_poisonNum)
            fprintf(wFile, "node00%ld:<n%ld_p> -> node00%ld:<n%lu_p> [ color = blue; ]\n", i, i, data->array[i].prev, data->array[i].prev);
    }

    fprintf(wFile, "\n");
    for (size_t i = 0; i < data->length; i++){
        if (data->array[i].value != c_poisonNum)
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

void insElem(data_t* data, size_t index, double value){
    assert(data != nullptr);
    //assert(index < data->freeCell);
    data->array[data->freeCell].next = index;
    data->array[data->freeCell].prev = data->array[index].prev;
    data->array[data->freeCell].value = value;
    data->array[data->array[index].prev].next = data->freeCell;
    data->array[index].prev = data->freeCell;
    
}

void delElem(data_t* data, size_t index){
    assert(data != nullptr);
    data->array[index].value = c_poisonNum;
    if (data->array[index].prev > 0)
        data->array[data->array[index].prev].next = data->array[index].next;
        
    data->array[data->array[index].next].prev = data->array[index].prev;
    data->freeCell = index;
}

void writeHtmlFile(const char* fileName, int numOfFiles){
    FILE* wFile = fopen(fileName, "wb");
    fprintf(wFile, "<pre>\n");
    for (int i = 0; i < numOfFiles; i++){
        fprintf(wFile, "<hr>\n");
        fprintf(wFile, "<img src=\"trees\\tree%d.png\">\n", i);
    }
}