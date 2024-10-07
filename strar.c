/*
This is assignment 2
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include "strar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
STRAR.C
Definitions of functions from the header.
*/

//CREATE COPY
strar createStrar(int size, char* arr[]){
    strar com;// we create com
    com.argPos=0;
    com.size=size;
    //memory allocation
    com.arr=(char **) malloc(size*sizeof(char*));
    if (com.arr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(139);
    }
    //we dublicate the contents
    for(int i=0;i<com.size;i++){
        com.arr[i]=strdup(arr[i]);
        //check for errors
        if(com.arr[i]==NULL){
            fprintf(stderr, "Strdup failed\n");
            exit(139);
        }
    }
    return com;
}

//CREATE EMPTY
strar createStrarEmp(int size){
    strar com;// we create com
    com.argPos=0;
    com.size=size;
    //we allocate memory and check for success
    com.arr=(char **) malloc(size*sizeof(char*));
    if (com.arr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(139);
    }
    return com;
}

//PRINT
void printstrar(strar str){
    //we print all the vaulues from the array of strings
    for(int i=0;i<str.size && str.arr[i]!=NULL; i++){
        printf("%s ",str.arr[i]);
    }
    printf("\n");
}

//FREE
void freestrar(strar* str){
    //we free the memory one by one
    for(int i=0;i<str->size; i++){
        free(str->arr[i]);
    }
    free(str->arr);
}
