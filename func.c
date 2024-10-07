#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "func.h"
#include "flags.h"
#include "strar.h"
#include <sys/wait.h>

/*
FUNC.C
Here i define the functiond from the header.
*/

//EXECUTE COMMAND
int executeCom(strar *com, int writeArg){
    //we check if we need to print before executing
    (writeArg) ? printstrar(*com):NULL;
    //we try exectuing it
    if(execvp(*(com->arr), com->arr)==-1){
        //there was an issue executing the given command
        fprintf(stderr,"xargs: %s: No such file in directory\n", com->arr[0]);
        exit(127);
        return -1;
    }
    return 0;
}

//GET ARGUMENTS FROM STDIN
strar getArgs(){
    int count=0;
    char* arr[MAX_ARGS];// we need a temporary array for input
    for (int i = 0; i < MAX_ARGS; i++) {
        // we allocate memory in it and check<
        arr[i] = malloc(MAX_ARG_LENGTH * sizeof(char));
        if (arr[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(139);
        }
    }
    int i=0;
    //we get input from stdin
    do{
        i=scanf("%s", arr[count]);
        count++;
    } while(i==1);
    //we create an instance of struct based on input
    strar inp = createStrar(count-1, arr);
    //we free the memory in the temporary array
    for (int i = 0; i < MAX_ARGS; i++) {
        free(arr[i]);
    }
    return inp;
    
}

//OPTIONS
void getOptions(strar *com, flags* flag){
    int opt;
    //we use getopt for options
    while((opt = getopt(com->size, com->arr, ":tn:j:"))!=-1){
        switch(opt){
            case 't':
                //writing arguements to stderr enabled
                flag->writeArg=1;
                (com->argPos)++;
                break;
            case 'n':
                //here the maximum number of arguements per command is defined
                int suc=sscanf(optarg, "%d", &(flag->maxArgs));
                //is the arguemnt check
                if (suc!=1){
                    fprintf(stderr, "xargs: invalid number %s for -n option\n", optarg);
                    exit(1);
                }
                //invalid int check
                if(flag->maxArgs<=0){
                    fprintf(stderr,"xargs: value %d for -n option should be >= 1\n", flag->maxArgs);
                    exit(1);
                }
                (com->argPos)+=2;
                break;
            case 'j':
                //here the maximum number jobs is told
                suc=sscanf(optarg, "%d", &(flag->par));
                //is the arguemnt check
                if (suc!=1){
                    fprintf(stderr, "xargs: invalid number %s for -j option\n", optarg);
                    exit(1);
                }
                //invalid int check
                if(flag->par<=0){
                    fprintf(stderr,"xargs: value %d for -j option should be >= 1\n", flag->par);
                    exit(1);
                }
                (com->argPos)+=2;
                break;
            case ':':
                //nothing to be done but call an error
            case '?':
                //unknown flag meaning invalid input
                fprintf(stderr,"xargs: invalid option -- '%c'\n", opt);
                fprintf(stderr,"Try 'xargs --help' for more information.\n");

                exit(1);
                break;
        }
    }
}

//CONSTRUCT COMMAND
void constrCom(strar *com,strar *inp, strar *exec, int maxArgs){
    int comArg=0;
    //we put the command that was passed to executable
    if(exec->argPos<exec->size){
        for(int i=exec->argPos; i<exec->size;i++){
            com->arr[comArg]=strdup(exec->arr[i]);
            comArg++;
        }
    } else {
        //if no command was passed we use echo
        com->arr[comArg]="/bin/echo";
        comArg++;
    }
    for (int i=0; i<maxArgs; i++){
        //we put the arguemnts from stdin
        com->arr[comArg]=strdup((inp->arr[inp->argPos]));
        comArg++;
        (inp->argPos)++;
    }
    //we terminate the array with NULL
    com->arr[comArg]=NULL;
}

//EXECUTE COMMAND IN PARALLEL
void executePar(strar* inp, strar* exec, flags* flag){
    //how many times do we execute commands?
    int passes = (inp->size % flag->maxArgs==0) ? 0 : 1;
    int fin=0;//number of finished processes
    int doing=-1;//how many process are done/in process
    int status; //status for wait pid

    passes += inp->size/flag->maxArgs ;
    //here we construct the commnads first
    //an array of commands
    strar coms[passes];

    for(int i = 0; i < passes ;i++){
        //how many argumnets from stdin do we get - args
        int args;
        if (flag->maxArgs<(inp->size-inp->argPos)) {
            args = flag->maxArgs;
        } else{
            args = inp->size-inp->argPos;
        }
        //the length of the command
        int comSize = exec->size-exec->argPos+args+1;
        coms[i] = createStrarEmp(comSize);
        //we construct command
        constrCom(&coms[i],inp,exec, args);
    }    

    while(fin < passes){
        int err=0;//was there an error?
        //we launch processes via fork
        for(int i=0; i<flag->par && doing < passes;i++){
            doing++;
            pid_t pid = fork();
            if (pid<0){
                exit(1);
            } else if(pid == 0){
                executeCom(&coms[doing],flag->writeArg);
            }
        }
        //we wait on them to finish
        for(int i=0; i<flag->par && (fin+i) < passes;i++){
            waitpid(0, &status, 0);
            fin++;//one more finished
            if (status!=0){
                err=1;
            }
        }
        //we do not have children left and can finish in case of error
        (err)? exit(127) : NULL;
    }
}