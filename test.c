#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long get_mem_usage(){
    struct rusage myusage;
    getrusage(RUSAGE_SELF,&myusage);
    return myusage.ru_maxrss;
}

int main(){
    FILE *fptr;
    fptr = fopen("text.txt","w");
    char *line1 = NULL, *line2 = NULL;
    size_t len1 = 0, len2 = 0;
    ssize_t read1 = 0, read2 = 0;
    fpos_t pos1 = 0,pos2 = 0;

/////////////////// Main Algo //////////////////////////


    for (int i = 0 ; i < 10000000; i++){
        char *num = (char *)(malloc(50));
        sprintf(num, "%d", rand());
        strncat(num,"\n",1);
        fprintf(fptr,"%s",num);
    }

/////////////////////////////////////////////////////////

/////////////////// Testings ////////////////////////////

    // if ((read1 = getline(&line1, &len1, fptr)) != -1){
    //     printf("%s",line1);
    //     pos1 += len1;
    //     line1 = NULL;
    // }
    // fclose(fptr);
    // fptr = fopen("test.txt", "w");
    // // printf("%lld\n",pos1);
    // fsetpos(fptr,&pos1);
    // fputs("Pokemon",fptr);
    // printf("%lld\n",pos1);




    // char* str1 = "1234";
    // char* str2 = "4321";
    // char *nums1 = (char *)(malloc(sizeof(char)*50));
    // char *nums2 = (char *)(malloc(sizeof(char)*50));
    // char *adder = ".txt";
    // sprintf(nums1, "%d", 10);
    // sprintf(nums2, "%d", 20);
    // strcat(nums1,nums2);
    // char* name = (char *)(malloc(sizeof(char)*50));
    // sprintf(name,"%s%s", nums1, adder);

    // printf("%s\n",name);


    //Basically Tyring to implement sorting files without actually
    //copying it to ram.
    // char *blank = "\n";

    // fpos_t selection_ptr = 0, iterator = 0, *minposition;
    
    // if ((read1 = getline(&line1, &len1, fptr)) != -1) {

    //     if ((read2 = getline(&line2, &len2, fptr)) != -1){

    //         iterator += read1;

    //         if (atoi(line1) > atoi(line2)){
    //             fsetpos(fptr, &selection_ptr);
    //             fwrite(line2,1,strlen(line1),fptr);
    //             fsetpos(fptr,&iterator);
    //             fwrite(line1,1,strlen(line2),fptr);
    //             // fprintf(fptr,"%s",line2);
    //         }

    //     }
    //     selection_ptr += read1;
    //     iterator = 0;
    //     fsetpos(fptr, &selection_ptr);
    // }
    // long baseline = get_mem_usage();
    // FILE *fptr;
    // fptr = fopen("text.txt","w");
    // for (int i = 0 ; i < 1000 ;i++){
    //     // printf("1\n");
    //     fptr[i] = fopen("text.txt","w");
    //     // for (int i = 0 ; i < 5000 ; i++){
    //     //     char *num = (char *)(malloc(50));
    //     //     sprintf(num, "%d", rand());
    //     //     printf("%s\n",num);
    //     //     strncat(num,"\n",1);
    //     //     fprintf(fptr[i],"%s",num);
    //     // }
    // }
    // for (int i = 0 ; i < 1000 ; i++){
    //     fclose(fptr[i]);
    // }
    // fpos_t *pos[1000];
    // for (int i = 0 ; i< 1000 ; i++){
    //     pos[i] = (fpos_t *)(malloc(sizeof(fpos_t)));
    // }
    // long final_usage = get_mem_usage();
    // printf("final_usage : %ld + %ld",baseline, final_usage - baseline);

    //Close the file pointer in same iteration. Else memory space gone.


}