#include <stdio.h>
#include <assert.h>

#include "../h_files/writeHtmlFile.h"


void writeHtmlFile(const char* fileName, int numOfFiles){
    assert(fileName != nullptr);

    FILE* wFile = fopen(fileName, "wb");
    
    if (wFile == nullptr)
    {
        printf("couldn't open file\n");
        return;
    }

    fprintf(wFile, "<pre>\n");
    for (int i = 0; i < numOfFiles; i++){
        fprintf(wFile, "<hr>\n");
        fprintf(wFile, "<img src=\"trees\\tree%d.png\">\n", i);
    }
}