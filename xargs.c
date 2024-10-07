/*
This is assignment 2
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "strar.h"
#include "flags.h"
#include "func.h"

//MAIN-------------------------------------------------------------------------
int main(int argc, char* argv[]){
    flags flag;//flags struct
    strar exec=createStrar(argc,argv);//arguements given to executable    
    strar inp;//arguements we receive from stdin

    //we set the deafult flag values
    flag.writeArg=0;
    flag.maxArgs=MAX_ARGS; 
    flag.par=1;   
    //we set the starting postition for exec
    exec.argPos=1;
    
    getOptions(&exec, &flag); //we set the options using getopt
    inp=getArgs(); //we receive the arguments from stdin
    //this is needed in cas maxArgs is not set by the user
    if (inp.size<flag.maxArgs){
        flag.maxArgs=inp.size;
    }
    //if no arguments nothing to do
    if (inp.size==0){
        printf("\n");//to match original
        return 0;
    }
    executePar(&inp, &exec, &flag); //we exectute the commands
    freestrar(&exec); //memory is freed
    freestrar(&inp);
    return 0;
}