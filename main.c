#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/resource.h>
#include<unistd.h>
#include "file_functions.h"
#include "sort_functions.h"

int main(int argc, char** argv){

    // printf("usage : %ld\n", get_mem_usage());
    long baseline = get_mem_usage();
    char *line;
    ssize_t read = 0;
    size_t len;
    int lines_count_per_file = 0;
    FILE *fptr;
    fptr = fopen(argv[1],"r");
    int file_count = read_file(fptr);
    long read_usage = get_mem_usage();
    printf("RAM usage for Segregating : %ld\n",read_usage - baseline);
    fclose(fptr);
    Final_Merger(file_count);
    long final_usage = get_mem_usage();
    printf("final_usage : %ld + %ld\n",baseline, final_usage - baseline);
}

