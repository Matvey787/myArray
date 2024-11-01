#include <stdio.h>
#include "../h_files/writeHtmlFile.h"


void writeHtmlFile(const char* fileName, int numOfFiles){
    FILE* wFile = fopen(fileName, "wb");
    fprintf(wFile, "<pre>\n");
    for (int i = 0; i < numOfFiles; i++){
        fprintf(wFile, "<hr>\n");
        fprintf(wFile, "<img src=\"trees\\tree%d.png\">\n", i);
    }
}