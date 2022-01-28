#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *fptr;
    fptr = fopen("text.txt","w");
    for (int i = 0 ; i < 50000 ; i++){
        char *num = (char *)(malloc(50));
        sprintf(num, "%d", rand());
        strncat(num,"\n",1);
        fprintf(fptr,"%s",num);
    }

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
}