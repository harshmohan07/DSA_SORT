#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include "file_functions.h"
#include "sort_functions.h"

#define CPU_SIZE 100000

void read_file(FILE* fptr, int *line_nums, char*** strings){
    char c;
    int line_count = 0, counter = 0;
    size_t size;
    c = fgetc((fptr));
    if (c != EOF){
        line_count = 1;
    }
    while (c != EOF){
        if (c == '\n'){
            line_count += 1;
        }
        c = fgetc(fptr);
    }
    rewind(fptr);
    char ** lines = malloc(sizeof(char *)*line_count);
    for (int i = 0 ; i < line_count ; i++){
        lines[i] = NULL;
    }
    for (c = getc(fptr); c != EOF; c = getc(fptr)){
        if (c == '\n'){
            counter += 1;
            continue;
        }else{
            if (lines[counter] == NULL){
                lines[counter] = (char *)(malloc(sizeof(c)*2));
                lines[counter][0] = c;
                lines[counter][1] = '\0';
            }else{
                size = strlen(lines[counter]);
                char *temp_str = lines[counter];
                lines[counter] = malloc(size+2);
                strcpy(lines[counter],temp_str);
                free(temp_str);
                temp_str = NULL;
                lines[counter][size] = c;
                lines[counter][size + 1] = '\0';
            }
        }
    }
    *line_nums = line_count;
    *strings = lines;
}


// This function is prone to increase RAM size wrt to number of lines file has.
int read_file_new(FILE *fptr, int line_count){
    FILE *temp_fptr,*fileptr;
    char *filenames = (char *)(malloc(sizeof(char)*20));
    char c;
    int counter = 0, file_count = 0;
    char *temp;
    char **string_ptrs = (char **)(malloc(sizeof(char *)*line_count));
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0, current_size = 0;
    while ((read = getline(&line, &len, fptr)) != -1) {
        current_size += read;
        if (current_size > CPU_SIZE){
            sprintf(filenames, "%d", file_count);
            strncat(filenames,".txt",4);
            temp_fptr = fopen(filenames,"w+");
            for (int h = 0 ; h < counter ; h++){
                fprintf(temp_fptr,"%s",string_ptrs[h]);
                current_size -= strlen(string_ptrs[h]);
            }
            fclose(temp_fptr);
            memset(filenames,0,20);
            file_count++;
            for (int i = 0 ; i < counter ; i++){
                temp = string_ptrs[i];
                free(temp);
                string_ptrs[i] = NULL;
            }
            counter = 0;
        }else if(current_size == CPU_SIZE){
            string_ptrs[counter] = (char *)malloc(sizeof(read));
            strcpy(string_ptrs[counter],line);
            counter++;
            sprintf(filenames, "%d", file_count);
            strncat(filenames,".txt",4);
            temp_fptr = fopen(filenames,"w");
            for (int h = 0 ; h < counter ; h++){
                fprintf(temp_fptr,"%s",string_ptrs[h]);
                current_size -= strlen(string_ptrs[h]);
            }
            fclose(temp_fptr);
            memset(filenames,0,20);
            file_count++;
            for (int i = 0 ; i < counter ; i++){
                temp = string_ptrs[i];
                free(temp);
                string_ptrs[i] = NULL;
            }
            if (feof(fptr)){
                continue;
            }
            counter = 0;
            continue;
        }
        string_ptrs[counter] = (char *)malloc(sizeof(read));
        strcpy(string_ptrs[counter],line);
        counter++;
    }
    if (string_ptrs[0] != NULL){
        sprintf(filenames, "%d", file_count);
        strncat(filenames,".txt",4);
        temp_fptr = fopen(filenames,"w");
        for (int h = 0 ; h < counter ; h++){
            fprintf(temp_fptr,"%s",string_ptrs[h]);
            current_size -= strlen(string_ptrs[h]);
        }
        fclose(temp_fptr);
        memset(filenames,0,20);
        file_count++;
        for (int i = 0 ; i < counter ; i++){
            temp = string_ptrs[i];
            free(temp);
            string_ptrs[i] = NULL;
        }
        counter = 0;
    }
    memset(filenames,0,20);
    fileptr = fopen("fileNames.txt","w");
    for (int i = 0 ; i < file_count  ; i++){
        sprintf(filenames, "%d", i);
        strncat(filenames,".txt\n",5);
        fprintf(fileptr,"%s",filenames);
        memset(filenames,0,20);
    }
    fclose(fileptr);
    return file_count;
}