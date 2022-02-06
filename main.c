#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/resource.h>
#include<unistd.h>
#include "file_functions.h"
#include "sort_functions.h"

int main(int argc, char** argv){
    int flags = 0;
    char *name= NULL;
    for (int i = 1 ; i < argc-1 ; i++){
        if (strcmp(argv[i],"-o") == 0){
            name = argv[i+1];
            i++;
        }else if (strcmp(argv[i],"-d") == 0){
            flags = flags | 1<<0;
        }else if (strcmp(argv[i],"-n") == 0){
            flags = flags | 1<<1;
        }else if (strcmp(argv[i],"-r") == 0){
            flags = flags | 1<<2;
        }
    }
    if (name == NULL){
        name = argv[argc-1];
    }
    printf("%d\n",flags);
    long baseline = get_mem_usage();
    FILE *fptr;
    fptr = fopen(argv[argc-1],"r");
    int file_count = read_file(fptr, flags);
    long read_usage = get_mem_usage();
    printf("RAM usage for Segregating : %ld\n",read_usage - baseline);
    fclose(fptr);
    Final_Merger(file_count, flags, name);
    long final_usage = get_mem_usage();
    printf("final_usage : %ld + %ld\n",baseline, final_usage - baseline);
}

