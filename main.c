#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/resource.h>
#include<unistd.h>
#include "file_functions.h"
#include "sort_functions.h"

int main(int argc, char** argv){
    int flags = 0,i,file_count = 0;
    fpos_t *name_file = (fpos_t *)(malloc(sizeof(fpos_t)));
    *name_file = 0;
    long baseline = get_mem_usage();
    FILE *fptr;
    char *name= NULL;
    for (i= 1 ; i < argc-1 ; i++){
        if (strcmp(argv[i],"-o") == 0){
            name = argv[i+1];
            i++;
        }else if (strcmp(argv[i],"-d") == 0){
            flags = flags | 1<<0;
        }else if (strcmp(argv[i],"-n") == 0){
            flags = flags | 1<<1;
        }else if (strcmp(argv[i],"-r") == 0){
            flags = flags | 1<<2;
        }else if (strcmp(argv[i],"-m") == 0){
            flags = flags | 1<<3;
            i++;
            break;
        }else if (strcmp(argv[i],"-c") == 0){
            flags = flags | 1<<4;
        }
    }
    if ((flags & 1<<3) != 0){
        if (name == NULL){
            name = argv[argc-1];
        }
        for (int j = i ; j < argc ; j++){
            fptr = fopen(argv[j],"r");
            read_file(fptr, flags,&file_count,name_file);
            fclose(fptr);
        }
        long read_usage = get_mem_usage();
        printf("RAM usage for Segregating : %ld\n",read_usage - baseline);
        printf("%d\n",file_count);
        Final_Merger(file_count, flags, name);
        long final_usage = get_mem_usage();
        printf("final_usage : %ld + %ld\n",baseline, final_usage - baseline);
    }else{
        if (name == NULL){
            name = argv[argc-1];
        }
        fptr = fopen(argv[argc-1],"r");
        int is_sorted = check_sorted(fptr, flags);
        if ((flags & 1<<4) != 0){
            if (is_sorted == 0){
                printf("File %s is already sorted\n",argv[argc-1]);
                return 0;
            }else{
                printf("File %s is not sorted\n",argv[argc-1]);
            }
        }
        read_file(fptr, flags,&file_count,name_file);
        fclose(fptr);
        long read_usage = get_mem_usage();
        printf("RAM usage for Segregating : %ld\n",read_usage - baseline);
        Final_Merger(file_count, flags, name);
        long final_usage = get_mem_usage();
        printf("final_usage : %ld + %ld\n",baseline, final_usage - baseline);
    }
}

