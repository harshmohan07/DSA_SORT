#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

void Merge(char*** strings,int low,int mid,int high){
    char **arr = *strings;
    int left= mid-low+1;
    int right= high-mid;

    char** L=malloc(sizeof(char *)*left);
    char** R=malloc(sizeof(char *)*right);
    int i;
    for(i=0;i<left;i++)
    {
        L[i]=malloc(sizeof(arr[low+i]));
        strcpy(L[i],arr[low+i]);
    }
    for(i=0;i<right;i++)
    {
        R[i]=malloc(sizeof(arr[mid+i+1]));
        strcpy(R[i],arr[mid+i+1]);
    }
    int j=0,k;
    i=0;
    k=low;
    while(i<left&&j<right)
    {
        if(strcmp(L[i],R[j])<0){
            
            char *s = arr[k];
            arr[k] = (char *)malloc(sizeof(L[i]));
            free(s);
            strcpy(arr[k++],L[i++]);
            
        }
        else {
            char *s = arr[k];
            arr[k] = (char *)malloc(sizeof(R[j]));
            free(s);
            strcpy(arr[k++],R[j++]);
        }
    }
    
    while(i<left){
        char *s = arr[k];
        arr[k] = (char *)malloc(sizeof(L[i]));
        free(s);
        strcpy(arr[k++],L[i++]);
    }
    while(j<right){
        char *s = arr[k];
        arr[k] = (char *)malloc(sizeof(R[j]));
        free(s);
        strcpy(arr[k++],R[j++]);
    }
}

void Merger (int file_count, char *** file_list){
    char *line = NULL, *temp1, *temp2;
    size_t len;
    ssize_t read = 0;
    char **files = *file_list;
    int current_lines_count = 0,min_ind;
    char **string_compares = (char **)(malloc(sizeof(char *)*file_count));
    char **string_compares_temp = (char **)(malloc(sizeof(char *)*file_count));
    FILE *fptr[file_count];
    char c[file_count];
    for (int i = 0 ; i < file_count ; i++){
        fptr[i] = fopen(files[i],"r");
    }
    while (1){
        for (int  i = 0 ; i < file_count ; i++){
            if (string_compares[i] == NULL){
                if ((read = getline(&line, &len, fptr[i])) != -1){
                    string_compares[i] = (char *)malloc(read);
                    strcpy(string_compares[i],line);
                    current_lines_count++;
                }
            }
        }
        for (int i = 0 ; i< file_count ; i++){
            if (string_compares[i] == NULL){
                string_compares_temp[i] = NULL;
            }else{
                string_compares_temp[i] = (char *)(malloc(sizeof(string_compares[i])));
                strcpy(string_compares_temp[i],string_compares[i]);
            }
        }

        if (current_lines_count == 0){
            break;
        }else if(current_lines_count == 1){
            for (int i = 0; i < file_count ; i++){
                if (string_compares[i] != NULL){
                    printf("%s",string_compares[i]);
                    free(string_compares[i]);
                    string_compares[i] = NULL;
                    current_lines_count--;
                    break;
                } 
            }
            continue;
        }else{
            //Here I'll Have to find which string is least lexiographically, 
            //print/save it and make that position NULL.
            for (int i = 0 ; i < file_count-1 ; i++){
                if (string_compares_temp[i] == NULL){
                    continue;
                }
                for (int j = i+1 ; j < file_count ; j++){
                    if (string_compares_temp[j] == NULL){
                        continue;
                    }else if (strcmp(string_compares_temp[i],string_compares_temp[j]) > 0){
                        temp1 = string_compares_temp[i];
                        temp2 = string_compares_temp[j];
                        string_compares_temp[i] = (char *)(malloc(sizeof(string_compares_temp[j])));
                        string_compares_temp[j] = (char *)(malloc(sizeof(string_compares_temp[i])));
                        strcpy(string_compares_temp[i],temp2);
                        strcpy(string_compares_temp[j],temp1);
                        free(temp1);
                        free(temp2);
                    }
                }
            }
            
            for (int i = 0 ; i < file_count ; i++){
                if (string_compares_temp[i] != NULL){
                    min_ind = i;
                    break;
                }
            }

            for (int i = 0; i < file_count ; i++){
                if (string_compares[i] != NULL){
                    if (strcmp(string_compares_temp[min_ind],string_compares[i]) == 0){
                        printf("%s",string_compares[i]);
                        free(string_compares[i]);
                        string_compares[i] = NULL;
                        current_lines_count -= 1;
                        break;
                    }
                }
            }

            for (int i = 0 ; i < file_count ; i++){
                free(string_compares_temp[i]);
                string_compares_temp[i] = NULL;
            }

        }
    }
}

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
    char c, *temp1, *temp2;
    size_t len;
    int lines_count_per_file = 0,counter = 0;
    char ** strings;
    char *files[file_count];
    filereader = fopen("fileNames.txt","r");
    for (int i = 0 ; i < file_count ; i++){
        read = getline(&line, &len, filereader);
        files[i] = (char *)(malloc(len));
        strcpy(files[i],line);
    } 
    fclose(filereader);

    for (int i = 0 ; i< file_count ; i++){
        char *name = files[i];
        if (name[strlen(name)-1] == '\n'){
            name[strlen(name)-1]= '\0';
        }
        fileptr = fopen(files[i],"r+");
        if (fileptr == NULL){
            printf("2\n");
        }
        c = fgetc(fileptr);
        if (c != EOF){
            lines_count_per_file = 1;
        }
        while (c != EOF){
            if (c == '\n'){
                lines_count_per_file += 1;
            }
            c = fgetc(fileptr);
        }
        rewind(fileptr);
        char **strings = (char**)(malloc(sizeof(char *)*lines_count_per_file));
        while ((read = getline(&line, &len, fileptr)) != -1) {
            strings[counter] = (char *)malloc(sizeof(read));
            strcpy(strings[counter],line);
            counter++;
        }
        counter = 0;
        rewind(fileptr);
        //Sorting Takes place here.
        for (int i = 0 ; i < lines_count_per_file-2 ; i++){
            if (strings[i] == NULL){
                continue;
            }for (int j = i+1 ;j< lines_count_per_file -1 ; j++){
                if (strings[j] == NULL){
                    continue;
                }else if (atoi(strings[i]) > atoi(strings[j])){
                    temp1 = strings[i];
                    temp2 = strings[j];
                    strings[i] = (char *)(malloc(sizeof(strings[j])));
                    strings[j] = (char *)(malloc(sizeof(strings[i])));
                    strcpy(strings[i],temp2);
                    strcpy(strings[j],temp1);
                    free(temp1);
                    free(temp2);
                }
            }
        }
        for(int i = 0 ; i < lines_count_per_file ; i++){
            fprintf(fileptr,"%s",strings[i]);
        }
        fclose(fileptr);
    }

    //Here Basically I have to mergefiles till I get a single
    //file which contains all the things sorted.
    // save_file_counter - for accounting the names where the new
    //                      file is stored.
    int file_counter = 0, iter = 0,array_counter = 0;
    FILE *tempfile1,*tempfile2,*newfile;
    char *adder = ".txt";
    char *rm = "rm ";
    char *line1 = NULL, *line2 = NULL,*temp_file_name;
    size_t len1 = 0, len2 = 0;
    ssize_t read1 = 0, read2 = 0;
    char *name = (char *)(malloc(sizeof(char)*50));
    char *nums1 = (char *)(malloc(sizeof(char)*50));
    char *nums2 = (char *)(malloc(sizeof(char)*50));
    while (file_count != 1){
        //Inititally to take two files and save it in third file.
        for (int i = 0 ; i < file_count/2 ; i++){
            char *name1 = files[array_counter];
            if (name1[strlen(name1)-1] == '\n'){
                name1[strlen(name1)-1]= '\0';
            }
            char *name2 = files[array_counter+1];
            if (name2[strlen(name2)-1] == '\n'){
                name2[strlen(name2)-1]= '\0';
            }
            array_counter+=2;
            tempfile1 = fopen(name1,"r");
            tempfile2 = fopen(name2,"r");
            sprintf(nums1, "%d", iter);
            sprintf(nums2, "%d", i);
            strcat(nums1,nums2);
            sprintf(name,"%s%s", nums1, adder);
            newfile = fopen(name,"w+");
            while (1){
                if (line1 == NULL){
                    if ((read1 = getline(&line1, &len1, tempfile1)) == -1){
                        break;
                    }
                }
                if (line2 == NULL){
                    if ((read1 = getline(&line2, &len2, tempfile2)) == -1){
                        break;
                    }
                }
                if (atoi(line1) < atoi(line2)){
                    fprintf(newfile,"%s",line1);
                    line1 = NULL;
                }else{
                    fprintf(newfile,"%s",line2);
                    line2 = NULL;
                }
            }
            if (line1 != NULL){
                fprintf(newfile,"%s",line1);
                line1 = NULL;
            }
            if (line2 != NULL){
                fprintf(newfile,"%s",line2);
                line2 = NULL;
            }
            while((read1 = getline(&line1, &len1, tempfile1)) != -1){
                fprintf(newfile,"%s",line1);
            }
            while((read2 = getline(&line2, &len2, tempfile2)) != -1){
                fprintf(newfile,"%s",line2);
            }
            fclose(tempfile1);
            fclose(tempfile2);
            fclose(newfile);
            memset(name,0,50);
            memset(nums1,0,50);
            memset(nums2,0,50);
            file_counter++;
        }

        // printf("%d\n",file_count);
        // printf("%d\n",file_counter);
        if (file_count%2 != 0){
            file_counter++;
        }

        if (file_counter == 1){
            for (int i = 0 ; i < file_count ; i++){
                if (files[i][strlen(files[i])-1] == '\n'){
                    files[i][strlen(files[i])-1]= '\0';
                }
                strcat(nums1,rm);
                strcat(nums1,files[i]);
                system(nums1);
                memset(nums1,0,50);
            }
            return;
        }

        if (file_count%2 == 0){
            for (int i = 0 ; i < file_count ; i++){
                if (files[i][strlen(files[i])-1] == '\n'){
                    files[i][strlen(files[i])-1]= '\0';
                }
                strcat(nums1,rm);
                strcat(nums1,files[i]);
                system(nums1);
                memset(nums1,0,50);
            }
            for (int i = 0 ; i < file_count ; i++){
                memset(files[i],0,strlen(files[i]));
            }
        }else{
            for (int i = 0 ; i < file_count-1 ; i++){
                if (files[i][strlen(files[i])-1] == '\n'){
                    files[i][strlen(files[i])-1]= '\0';
                }
                strcat(nums1,rm);
                strcat(nums1,files[i]);
                system(nums1);
                memset(nums1,0,50);
            }
            for (int i = 0 ; i < file_count-1 ; i++){
                memset(files[i],0,strlen(files[i]));
            }
            temp_file_name = files[file_count-1];
        }

        for (int i = 0 ; i < file_counter; i++){
            
            sprintf(nums1, "%d", iter);
            sprintf(nums2, "%d", i);
            strcat(nums1,nums2);
            sprintf(name,"%s%s", nums1, adder);
            strcpy(files[i],name);
            memset(name,0,50);
            memset(nums1,0,50);
            memset(nums2,0,50);
        }

        if (file_count%2 != 0){
            strcpy(files[file_counter-1],temp_file_name);
            free(temp_file_name);
            temp_file_name = NULL;
        }
        file_count = file_counter;
        file_counter = 0;
        array_counter = 0;
        iter++;
        printf("%d\n",file_count);
        for (int i = 0 ; i< file_count ; i++){
            printf("%s\n",files[i]);
        }
    }

}