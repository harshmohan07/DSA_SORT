#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include "file_functions.h"
#include "sort_functions.h"

#define CPU_SIZE 100000

int read_file(FILE *fptr){
    FILE *temp_fptr;
    char *filenames = (char *)(malloc(sizeof(char)*20));
    int file_count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0, current_size = 0;
    sprintf(filenames, "%d", file_count);
    strncat(filenames,".txt",4);
    temp_fptr = fopen(filenames,"w");
    memset(filenames,0,20);
    while ((read = getline(&line, &len, fptr)) != -1) {
        current_size += read;
        if (current_size >= CPU_SIZE){
            fclose(temp_fptr);
            file_count++;
            current_size = 0;
            current_size += read;
            sprintf(filenames, "%d", file_count);
            strncat(filenames,".txt",4);
            temp_fptr = fopen(filenames,"w");
            memset(filenames,0,20);
        }
        fprintf(temp_fptr,"%s",line);
    }
    fclose(fptr);
    fclose(temp_fptr);

    memset(filenames,0,50);
    fptr = fopen("fileNames.txt","w");
    for (int i = 0 ; i <= file_count  ; i++){
        sprintf(filenames, "%d", i);
        strncat(filenames,".txt\n",5);
        fprintf(fptr,"%s",filenames);
        memset(filenames,0,50);
    }
    fclose(fptr);
    free(filenames);
    return file_count+1;
}