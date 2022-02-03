#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<sys/resource.h>
#include<unistd.h>

long get_mem_usage(){
    struct rusage myusage;
    getrusage(RUSAGE_SELF,&myusage);
    return myusage.ru_maxrss;
}

void Merge(char*** strings,int low,int mid,int high){
    char **arr = *strings;
    int left= mid-low+1;
    int right= high-mid;

    char** L=malloc(sizeof(char *)*left);
    char** R=malloc(sizeof(char *)*right);
    int i;
    for(i=0;i<left;i++)
    {
        L[i]=arr[low+i];
    }
    for(i=0;i<right;i++)
    {
        R[i]=arr[mid+i+1];
    }
    int j=0,k;
    i=0;
    k=low;
    while(i<left&&j<right)
    {
        if(atoi(L[i]) < atoi(R[j])){
            arr[k] = (char *)malloc(sizeof(L[i]));
            strcpy(arr[k++],L[i++]); 
        }
        else {
            arr[k] = (char *)malloc(sizeof(R[j]));
            strcpy(arr[k++],R[j++]);
        }
    }
    
    while(i<left){
        arr[k] = (char *)malloc(sizeof(L[i]));
        strcpy(arr[k++],L[i++]);
    }
    while(j<right){
        arr[k] = (char *)malloc(sizeof(R[j]));
        strcpy(arr[k++],R[j++]);
    }
    for(i=0;i<left;i++)
    {
        free(L[i]);
        L[i] = NULL;
    }
    for(i=0;i<right;i++)
    {
        free(R[i]);
        R[i] = NULL;
    }
    free(L);
    free(R);

}

void Merger (int file_count){
    char *line = NULL, *temp1, *temp2, *temp3;
    size_t len;
    ssize_t read = 0;
    char *rm = "rm ";
    char *files[file_count];
    fpos_t *pos[file_count];
    for (int i = 0 ; i < file_count ; i++){
        pos[i] = (fpos_t *)(malloc(sizeof(fpos_t)));
        *pos[i] = 0;
    }
    FILE *filereader = fopen("fileNames.txt","r");
    for (int i = 0 ; i < file_count ; i++){
        read = getline(&line, &len, filereader);
        files[i] = (char *)(malloc(len));
        strcpy(files[i],line);
        if (files[i][strlen(files[i])-1] == '\n'){
            files[i][strlen(files[i])-1]= '\0';
        }
    } 
    fclose(filereader);
    int current_lines_count = 0,min_ind = 0,count = 0;
    char **string_compares = (char **)(malloc(sizeof(char *)*file_count));
    for (int i = 0; i < file_count ; i++){
        string_compares[i] = NULL;
    }
    FILE *fptr;
    FILE* output = fopen("output.txt","w");
    while (1){
        for (int  i = 0 ; i < file_count ; i++){
            if (string_compares[i] == NULL){
                fptr = fopen(files[i],"r");
                fsetpos(fptr,pos[i]);
                if ((read = getline(&line, &len, fptr)) != -1){
                    string_compares[i] = (char *)malloc(read);
                    strcpy(string_compares[i],line);
                    *pos[i] += read;
                    current_lines_count++;
                }
                fclose(fptr);
            }
        }
        if (current_lines_count == 0){
            break;
        }else if(current_lines_count == 1){
            for (int i = 0; i < file_count ; i++){
                if (string_compares[i] != NULL){
                    fprintf(output,"%s",string_compares[i]);
                    count++;
                    free(string_compares[i]);
                    string_compares[i] = NULL;
                    current_lines_count--;
                    break;
                } 
            }
        }else{
            //Here I'll Have to find which string is least lexiographically, 
            //print/save it and make that position NULL.
            for (int i = 0 ; i < file_count-1 ; i++){
                if (string_compares[i] != NULL){
                    temp3 = string_compares[i];
                    min_ind = i;
                    break;
                }
            }
            for (int i = 0 ; i < file_count-1 ; i++){
                if (string_compares[i] == NULL){
                    continue;
                }
                if (atoi(string_compares[i]) < atoi(temp3)){
                    temp3 = string_compares[i];
                    min_ind = i;
                }
            }
            fprintf(output,"%s",string_compares[min_ind]);
            count++;
            free(string_compares[min_ind]);
            string_compares[min_ind] = NULL;
            temp3 = NULL;
            current_lines_count--;
        }
    }
    char *remove = (char *)(malloc(sizeof(char)*20));
    for (int i = 0 ; i < file_count ; i++){
        strcpy(remove,rm);
        strcat(remove,files[i]);
        system(remove);
        free(files[i]);
        files[i] = NULL;
        memset(remove,0,20);
    }
    fclose(output);
}


// void Merger (int file_count){
//     char *line = NULL, *temp1, *temp3;
//     size_t len;
//     ssize_t read = 0;
//     char *files[file_count];
//     fpos_t *pos[file_count];
//     FILE *filereader = fopen("fileNames.txt","r");
//     FILE* output = fopen("output.txt","w");
//     for (int i = 0 ; i < file_count ; i++){
//         pos[i] = (fpos_t *)(malloc(sizeof(fpos_t)));
//         *pos[i] = 0;
//     }
//     for (int i = 0 ; i < file_count ; i++){
//         read = getline(&line, &len, filereader);
//         files[i] = (char *)(malloc(len));
//         strcpy(files[i],line);
//         if (files[i][strlen(files[i])-1] == '\n'){
//             files[i][strlen(files[i])-1]= '\0';
//         }
//     } 
//     fclose(filereader);
//     int current_lines_count = 0,min_ind = 0;
//     char *string_ptr = NULL;
//     FILE *fptr;
//     while (1){
//         for (int  i = 0 ; i < file_count ; i++){
//             if (string_ptr == NULL){
//                 fptr = fopen(files[i],"r");
//                 fsetpos(fptr,pos[i]);
//                 if ((read = getline(&line, &len, fptr)) != -1){
//                     string_ptr = (char *)malloc(read);
//                     strcpy(string_ptr,line);
//                     *pos[i] += read;
//                     current_lines_count++;
//                 }
//                 fclose(fptr);
//             }else{
//                 fptr = fopen(files[i],"r");
//                 fsetpos(fptr,pos[i]);
//                 if ((read = getline(&line, &len, fptr)) != -1){
//                     if (atoi(string_ptr) < atoi(line)){
//                         temp1 = string_ptr;
//                         string_ptr = (char *)malloc(read);
//                         free(temp1);
//                         strcpy(string_ptr,line);
//                         *pos[i] += read;
//                         current_lines_count++;
//                     }
//                 }
//                 fclose(fptr);
//             }
//         }
//         if (current_lines_count == 0){
//             break;
//         }else {
//             fprintf(output,"%s",string_ptr);
//             free(string_ptr);
//             string_ptr = NULL;
//             current_lines_count--;
//         }
//     }
//     fclose(output);
// }

void MergeSort(char*** arr,int low,int high){
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSort(arr,low,mid);
        MergeSort(arr,mid+1,high);
        Merge(arr,low,mid,high);
    }
}

//In the function to make, 
//1. Sort one of the two files using Merge Sort (Can be done).
//2. Merge two files and name it seperatly.

void Final_Merger(int file_count){
    FILE *fileptr, *filereader;
    char *line;
    ssize_t read = 0;
    size_t len;
    char *temp1, *temp2;
    int lines_count_per_file = 0,counter = 0;
    char ** strings;
    char **files = (char **)malloc(sizeof(char *)*file_count);
    filereader = fopen("fileNames.txt","r");
    
    if (filereader == NULL){
        printf("Gandla\n");
    }
    for (int i = 0 ; i < file_count ; i++){
        read = getline(&line, &len, filereader);
        files[i] = (char *)(malloc(len));
        strcpy(files[i],line);
        if (files[i][strlen(files[i])-1] == '\n'){
            files[i][strlen(files[i])-1]= '\0';
        }
    } 
    fclose(filereader);
    long initial_initial_usage = get_mem_usage();

    printf("Sorting the file : \n");
    for (int i = 0 ; i< file_count ; i++){
        char *name = files[i];
        fileptr = fopen(files[i],"r+");
        if (fileptr == NULL){
            printf("3n");
        }
        while ((read = getline(&line, &len, fileptr)) != -1){
            lines_count_per_file += 1;
        }
        rewind(fileptr);
        strings = (char**)(malloc(sizeof(char *)*lines_count_per_file));
        while ((read = getline(&line, &len, fileptr)) != -1) {
            strings[counter] = (char *)malloc(sizeof(read));
            strcpy(strings[counter],line);
            counter++;
        }
        counter = 0;
        rewind(fileptr);
        
        // MergeSort(&strings,0,lines_count_per_file-2);
        for (int i = 0 ; i < lines_count_per_file-1 ; i++){
            for (int j = i+1 ; j < lines_count_per_file ; j++){
                if (atoi(strings[i]) > atoi(strings[j])){
                    temp1 = strings[i];
                    temp2 = strings[j];
                    strings[i] = temp2;
                    strings[j] = temp1;
                }
            }
        }
        
        for(int i = 0 ; i < lines_count_per_file ; i++){
            fprintf(fileptr,"%s",strings[i]);
        }
        for(int i = 0 ; i < lines_count_per_file ; i++){
            free(strings[i]);
            strings[i] = NULL;
        } 
        free(strings);
        strings = NULL;
        fclose(fileptr);
        lines_count_per_file = 0;
    }
    printf("Sorting Finished!\n");
    long initial_usage = get_mem_usage();
    printf("RAM usage for Sorting : %ld \n", initial_usage - initial_initial_usage);
    Merger(file_count);
    long final_usage = get_mem_usage();
    printf("RAM usage for Merger : %ld \n", final_usage - initial_usage);
}