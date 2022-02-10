#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<sys/resource.h>
#include<unistd.h>

char *temp1 = NULL;
char **arr = NULL;
char *pivot = NULL;

long get_mem_usage(){
    struct rusage myusage;
    getrusage(RUSAGE_SELF,&myusage);
    return myusage.ru_maxrss;
}

int partition_int_reverse(char *** a, int low, int high)
{
    arr = *a;
    pivot = arr[high];
    int i = (low - 1); 
 
    for (int j = low; j <= high - 1; j++){
        if (atoi(arr[j]) > atoi(pivot)){
            i++;
            temp1 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp1;
        }
    }
    temp1 = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp1;
    temp1 = NULL;
    arr = NULL;
    return (i + 1);
}

int partition_int(char *** a, int low, int high)
{
    arr = *a;
    pivot = arr[high];
    int i = (low - 1); 
 
    for (int j = low; j <= high - 1; j++){
        if (atoi(arr[j]) < atoi(pivot)){
            i++;
            temp1 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp1;
        }
    }
    temp1 = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp1;
    temp1 = NULL;
    arr = NULL;
    return (i + 1);
}

int partition_strings_reverse (char *** a, int low, int high)
{
    arr = *a;
    pivot = arr[high];
    int i = (low - 1); 
 
    for (int j = low; j <= high - 1; j++){
        if (strcmp(arr[j] ,pivot) > 0){
            i++;
            temp1 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp1;
        }
    }
    temp1 = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp1;
    temp1 = NULL;
    arr = NULL;
    return (i + 1);
}

int partition_strings (char *** a, int low, int high)
{
    arr = *a;
    pivot = arr[high];
    int i = (low - 1); 
 
    for (int j = low; j <= high - 1; j++){
        if (strcmp(arr[j] ,pivot) < 0){
            i++;
            temp1 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp1;
        }
    }
    temp1 = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp1;
    temp1 = NULL;
    arr = NULL;
    return (i + 1);
}
 
void quickSort(char *** arr, int low, int high, int flags)
{
    if ((flags & 1<<1) != 0){
        if ((flags & 1<<2) != 0){
            if (low < high){
                int pi = partition_int_reverse(arr, low, high);
                quickSort(arr, low, pi - 1,flags);
                quickSort(arr, pi + 1, high,flags);
            }
        }else{
            if (low < high){
                int pi = partition_int(arr, low, high);
                quickSort(arr, low, pi - 1,flags);
                quickSort(arr, pi + 1, high,flags);
            }
        }
    }else if ((flags & 1<<0) != 0){
        if ((flags & 1<<2) != 0){
            if (low < high){
                int pi = partition_strings_reverse(arr, low, high);
                quickSort(arr, low, pi - 1,flags);
                quickSort(arr, pi + 1, high,flags);
            }
        }else{
            if (low < high){
                int pi = partition_strings(arr, low, high);
                quickSort(arr, low, pi - 1,flags);
                quickSort(arr, pi + 1, high,flags);
            }
        }
    }
}

//Make changes in Merger to make it fast.

void Merger(int file_count ,int flags ,char *name_of_file){
    char *line = NULL;
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
    int current_lines_count = 0,min_ind = 0;
    char **string_compares = (char **)(malloc(sizeof(char *)*file_count));
    for (int i = 0; i < file_count ; i++){
        string_compares[i] = NULL;
    }
    FILE *fptr;
    FILE* output = fopen(name_of_file,"w");
    for (int  i = 0 ; i < file_count ; i++){
        if (string_compares[i] == NULL && pos[i] != NULL){
            fptr = fopen(files[i],"r");
            fsetpos(fptr,pos[i]);
            if ((read = getline(&line, &len, fptr)) != -1){
                string_compares[i] = (char *)malloc(read);
                strcpy(string_compares[i],line);
                *pos[i] += read;
                current_lines_count++;
            }else{
                free(pos[i]);
                pos[i] = NULL;
            }
            fclose(fptr);
        }
    }
    if ((flags & 1<<1) != 0){
        if ((flags & 1<<2) != 0){    
            while (1){
                if (string_compares[min_ind] == NULL && pos[min_ind] != NULL){
                    fptr = fopen(files[min_ind],"r");
                    fsetpos(fptr,pos[min_ind]);
                    if ((read = getline(&line, &len, fptr)) != -1){
                        string_compares[min_ind] = (char *)malloc(read);
                        strcpy(string_compares[min_ind],line);
                        *pos[min_ind] += read;
                        current_lines_count++;
                    }else{
                        free(pos[min_ind]);
                        pos[min_ind] = NULL;
                    }
                    fclose(fptr);
                }
                // printf("%d\n",current_lines_count);
                if (current_lines_count == 0){
                    break;
                }else if(current_lines_count == 1){
                    for (int i = 0; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            fprintf(output,"%s",string_compares[i]);
                            free(string_compares[i]);
                            string_compares[i] = NULL;
                            min_ind = i;
                            current_lines_count--;
                            break;
                        } 
                    }
                }else{
                    //Here I'll Have to find which string is least lexiographically, 
                    //print/save it and make that position NULL.
                    for (int i = 0 ; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            temp1 = string_compares[i];
                            min_ind = i;
                            break;
                        }
                    }
                    for (int i = min_ind ; i < file_count ; i++){
                        if (string_compares[i] == NULL){
                            continue;
                        }
                        if (atoi(string_compares[i]) > atoi(temp1)){
                            temp1 = string_compares[i];
                            min_ind = i;
                        }
                    }
                    fprintf(output,"%s",string_compares[min_ind]);
                    free(string_compares[min_ind]);
                    string_compares[min_ind] = NULL;
                    temp1 = NULL;
                    current_lines_count--;
                }
            }
        }else{
            while (1){
                if (string_compares[min_ind] == NULL && pos[min_ind] != NULL){
                    fptr = fopen(files[min_ind],"r");
                    fsetpos(fptr,pos[min_ind]);
                    if ((read = getline(&line, &len, fptr)) != -1){
                        string_compares[min_ind] = (char *)malloc(read);
                        strcpy(string_compares[min_ind],line);
                        *pos[min_ind] += read;
                        current_lines_count++;
                    }else{
                        free(pos[min_ind]);
                        pos[min_ind] = NULL;
                    }
                    fclose(fptr);
                }
                // printf("%d\n",current_lines_count);
                if (current_lines_count == 0){
                    break;
                }else if(current_lines_count == 1){
                    for (int i = 0; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            fprintf(output,"%s",string_compares[i]);
                            free(string_compares[i]);
                            string_compares[i] = NULL;
                            min_ind = i;
                            current_lines_count--;
                            break;
                        } 
                    }
                }else{
                    //Here I'll Have to find which string is least lexiographically, 
                    //print/save it and make that position NULL.
                    for (int i = 0 ; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            temp1 = string_compares[i];
                            min_ind = i;
                            break;
                        }
                    }
                    for (int i = min_ind+1 ; i < file_count ; i++){
                        if (string_compares[i] == NULL){
                            continue;
                        }
                        if (atoi(string_compares[i]) < atoi(temp1)){
                            temp1 = string_compares[i];
                            min_ind = i;
                        }
                    }
                    fprintf(output,"%s",string_compares[min_ind]);
                    free(string_compares[min_ind]);
                    string_compares[min_ind] = NULL;
                    temp1 = NULL;
                    current_lines_count--;
                }
            }
        }
    }else if ((flags & 1<<0) != 0){
        if ((flags & 1<<2) != 0){
            while (1){
                if (string_compares[min_ind] == NULL && pos[min_ind] != NULL){
                    fptr = fopen(files[min_ind],"r");
                    fsetpos(fptr,pos[min_ind]);
                    if ((read = getline(&line, &len, fptr)) != -1){
                        string_compares[min_ind] = (char *)malloc(read);
                        strcpy(string_compares[min_ind],line);
                        *pos[min_ind] += read;
                        current_lines_count++;
                    }else{
                        free(pos[min_ind]);
                        pos[min_ind] = NULL;
                    }
                    fclose(fptr);
                }
                // printf("%d\n",current_lines_count);
                if (current_lines_count == 0){
                    break;
                }else if(current_lines_count == 1){
                    for (int i = 0; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            fprintf(output,"%s",string_compares[i]);
                            free(string_compares[i]);
                            string_compares[i] = NULL;
                            min_ind = i;
                            current_lines_count--;
                            break;
                        } 
                    }
                }else{
                    //Here I'll Have to find which string is least lexiographically, 
                    //print/save it and make that position NULL.
                    for (int i = 0 ; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            temp1 = string_compares[i];
                            min_ind = i;
                            break;
                        }
                    }
                    for (int i = 0 ; i < file_count ; i++){
                        if (string_compares[i] == NULL){
                            continue;
                        }
                        if (strcmp(string_compares[i],temp1) > 0){
                            temp1 = string_compares[i];
                            min_ind = i;
                        }
                    }
                    fprintf(output,"%s",string_compares[min_ind]);
                    free(string_compares[min_ind]);
                    string_compares[min_ind] = NULL;
                    temp1 = NULL;
                    current_lines_count--;
                }
            }
        }else{
            while (1){
                if (string_compares[min_ind] == NULL && pos[min_ind] != NULL){
                    fptr = fopen(files[min_ind],"r");
                    fsetpos(fptr,pos[min_ind]);
                    if ((read = getline(&line, &len, fptr)) != -1){
                        string_compares[min_ind] = (char *)malloc(read);
                        strcpy(string_compares[min_ind],line);
                        *pos[min_ind] += read;
                        current_lines_count++;
                    }else{
                        free(pos[min_ind]);
                        pos[min_ind] = NULL;
                    }
                    fclose(fptr);
                }
                // printf("%d\n",current_lines_count);
                if (current_lines_count == 0){
                    break;
                }else if(current_lines_count == 1){
                    for (int i = 0; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            fprintf(output,"%s",string_compares[i]);
                            free(string_compares[i]);
                            string_compares[i] = NULL;
                            min_ind = i;
                            current_lines_count--;
                            break;
                        } 
                    }
                }else{
                    //Here I'll Have to find which string is least lexiographically, 
                    //print/save it and make that position NULL.
                    for (int i = 0 ; i < file_count ; i++){
                        if (string_compares[i] != NULL){
                            temp1 = string_compares[i];
                            min_ind = i;
                            break;
                        }
                    }
                    for (int i = 0 ; i < file_count ; i++){
                        if (string_compares[i] == NULL){
                            continue;
                        }
                        if (strcmp(string_compares[i],temp1) < 0){
                            temp1 = string_compares[i];
                            min_ind = i;
                        }
                    }
                    fprintf(output,"%s",string_compares[min_ind]);
                    free(string_compares[min_ind]);
                    string_compares[min_ind] = NULL;
                    temp1 = NULL;
                    current_lines_count--;
                }
            }
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

//In the function to make, 
//1. Sort one of the two files using Merge Sort (Can be done).
//2. Merge two files and name it seperatly.

void Final_Merger(int file_count, int flags, char *name_of_file){
    FILE *fileptr, *filereader;
    char *line = NULL;
    ssize_t read = 0;
    size_t len;
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

        quickSort(&strings, 0 ,lines_count_per_file-1, flags);
        
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
    long initial_usage = get_mem_usage();
    printf("RAM usage for Sorting : %ld \n", initial_usage - initial_initial_usage);
    Merger(file_count,flags,name_of_file);
    long final_usage = get_mem_usage();
    printf("RAM usage for Merger : %ld \n", final_usage - initial_usage);
}