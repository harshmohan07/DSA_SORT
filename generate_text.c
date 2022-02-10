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
    fptr = fopen("text2_10MB.txt","w");

    for (int i = 0 ; i < 1000000; i++){
        char *num = (char *)(malloc(50));
        sprintf(num, "%d", rand());
        strncat(num,"\n",1);
        fprintf(fptr,"%s",num);
    }

}