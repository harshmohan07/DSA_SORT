#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/resource.h>
#include<unistd.h>
#include "file_functions.h"
#include "sort_functions.h"

long get_mem_usage(){
    struct rusage myusage;
    getrusage(RUSAGE_SELF,&myusage);
    return myusage.ru_maxrss;
}

int main(int argc, char** argv){

    // printf("usage : %ld\n", get_mem_usage());
    long baseline = get_mem_usage();

    FILE *fptr, *temp_fptr, *temp_file;
    char c,k;
    int line_count = 0, counter = 0, buffer_count = 1, file_char_count = 0, iter_size = 0;
    char *temp;
    size_t size, total_size = 0;
    
    // if (argc == 1){
    //     printf("Invalid number of Arguments!");
    // }else if (argc == 2){
    //     // Only Implementation of '--help' remainning in two output range.
    //     if (strcmp(argv[1],"--version") == 0){
    //         printf("Current Version : 1.0.0\n");
    //         printf("Made by Harshmohan Kulkarni\n");
    //     }else{
    //         fptr = fopen(argv[1],"r");
    //         if(fptr == NULL){
    //             perror("File not found");
    //             return errno;
	// 	    }
    //         int line_count;
    //         char **string;
    //         read_file(fptr,&line_count, &string);
    //         MergeSort(&string,0,line_count-1);
    //         for (int i = 0 ; i < line_count ; i++){
    //             printf("%s\n",string[i]);
    //         }
    //     }
    // }

    //Merge Sort Implementation.
    //1. Sort the Data into pieces of CPU Size.
    //2. Merge Sort them and then store them into external files.
    //3. Write a Merger Function which will take all of them into account
    //   and use k-Ways Merge to sort each one of them into seperate files.

    fptr = fopen(argv[1],"r");
    c = getc(fptr);
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
    int file_count = read_file_new(fptr,line_count);
    fclose(fptr);
    long final_usage = get_mem_usage();
    // printf("%d\n",file_count);
    Final_Merger(file_count);
    printf("final_usage : %ld + %ld",baseline, final_usage - baseline);
    // temp_file = fopen("names.txt","w");
    // for (int i = 0 ; i < file_count ; i++){
    //     printf("%s\n",file_list[i]);
    // }
    // printf("%d\n",file_count);
    // Merger(file_count, &file_list);
}

