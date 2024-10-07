/*
This is assignment 2
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#define MAX_ARGS 1000000
#define MAX_ARG_LENGTH 100

#ifndef STRAR_H
#define STRAR_H

/*
STRAR.H
In this header the struct for an array of strings is defined as well as
its functions are decalred.
*/

/*
STRUCT
This is a struct i use for passing multi string arrays. It has:
size - length
argPos - element where we stopped
arr - array of string we store
*/
typedef struct strArray{
    int size;
    int argPos;
    char** arr;
} strar;

/*
CREATE strar BY COPY
create a copy of array of strings following the struct.
return the new strar
int size - number of strings
char* arr - the strings we need to copy
*/
strar createStrar(int size, char* arr[]);

/*
CREATE EMPTY
creates an empty strar struct and allocates memory.
return the new strar
int size - the number of elements
*/
strar createStrarEmp(int size);

/*
PRINT
this function prints a given struct.
strar str - the strint struct for printing
*/
void printstrar(strar str);

/*
FREE
This function frees the memory of the struct.
strar* str - struct pointer to be freed
*/
void freestrar(strar* str);
#endif