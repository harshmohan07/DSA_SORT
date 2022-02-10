#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include "file_functions.h"

#define CPU_SIZE 1000000
//Divided by 10 actually while using because while running ,
//Recursion Stack occupies some excess space and to keep that below our
//required size, we usually divide files 10x smaller than the actual RAM
//to be utilised. 


int check_sorted (FILE *fptr, int flags){
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char *temp = NULL;
    if ((flags & 1<<1) != 0){
        if ((flags & 1<<2) != 0){
            while ((read = getline(&line, &len, fptr)) != -1){
                if (temp == NULL){
                    temp = line;
                    line = NULL;
                    continue;
                }else{
                    if (atoi(temp) < atoi(line)){
                        temp = NULL;
                        line = NULL;
                        rewind(fptr);
                        return 1;    
                    }else{
                        temp = line;
                        line = NULL;
                    }
                }
            }
            return 0;
        }else{
            while ((read = getline(&line, &len, fptr)) != -1){
                if (temp == NULL){
                    temp = line;
                    line = NULL;
                    continue;
                }else{
                    if (atoi(temp) > atoi(line)){
                        temp = NULL;
                        line = NULL;
                        rewind(fptr);
                        return 1;    
                    }else{
                        temp = line;
                        line = NULL;
                    }
                }
            }
            temp = NULL;
            line = NULL;
            rewind(fptr);
            return 0;
        }
    }else if ((flags & 1<<0) != 0){
        if ((flags & 1<<2) != 0){
            while ((read = getline(&line, &len, fptr)) != -1){
                if (temp == NULL){
                    temp = line;
                    line = NULL;
                    continue;
                }else{
                    if (strcmp(temp,line) < 0){
                        temp = NULL;
                        line = NULL;
                        rewind(fptr);
                        return 1;    
                    }else{
                        temp = line;
                        line = NULL;
                    }
                }
            }
            return 0;
        }else{
            while ((read = getline(&line, &len, fptr)) != -1){
                if (temp == NULL){
                    temp = line;
                    line = NULL;
                    continue;
                }else{
                    if (strcmp(temp,line) > 0){
                        temp = NULL;
                        line = NULL;
                        rewind(fptr);
                        return 1;    
                    }else{
                        temp = line;
                        line = NULL;
                    }
                }
            }
            return 0;
        }
    }
    return 0;
}

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
        if (current_size >= CPU_SIZE/10){
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
    if (initial_file_count == 0){
        fptr = fopen("fileNames.txt","w");
    }else{
        fptr = fopen("fileNames.txt","r+");
    }
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
