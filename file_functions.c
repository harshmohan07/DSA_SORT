#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include "file_functions.h"

#define CPU_SIZE 100000
//280650 lines sorted per minute for 100000 bytes RAM.

void read_file(FILE *fptr, int flags, int *file_count, fpos_t *name_file){
    int initial_file_count = *file_count;
    FILE *temp_fptr;
    char *filenames = (char *)(malloc(sizeof(char)*20));
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0, current_size = 0;
    sprintf(filenames, "%d", *file_count);
    strncat(filenames,".txt",4);
    temp_fptr = fopen(filenames,"w");
    memset(filenames,0,20);
    while ((read = getline(&line, &len, fptr)) != -1) {
        current_size += read;
        if (current_size >= CPU_SIZE){
            fclose(temp_fptr);
            (*file_count) += 1;
            current_size = 0;
            current_size += read;
            sprintf(filenames, "%d", *file_count);
            strncat(filenames,".txt",4);
            temp_fptr = fopen(filenames,"w");
            memset(filenames,0,20);
        }
        fprintf(temp_fptr,"%s",line);
    }
    fclose(fptr);
    fclose(temp_fptr);
    memset(filenames,0,50);
    fptr = fopen("fileNames.txt","r+");
    fsetpos(fptr,name_file);
    for (int i = initial_file_count ; i <= *file_count  ; i++){
        sprintf(filenames, "%d", i);
        strncat(filenames,".txt\n",5);
        fprintf(fptr,"%s",filenames);
        memset(filenames,0,50);
    }
    fgetpos(fptr,name_file);
    fclose(fptr);
    free(filenames);
    *file_count += 1;
}