/*
This is assignment 2
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include "strar.h"
#include "flags.h"

/*
FUNC.H
In this geader I declared key functions which are used in mu programm
*/

#ifndef FUNC_H
#define FUNC_H

/*
EXECUTE COMMAND
It checks that a command is correctly executed and prints error otherwise.
com - pointer to string array struct
writeArg - if the command is printed before execuion or not
*/
int executeCom(strar *com, int writeArg);

/*
GET ARGUMENTS FROM STDIN
This function get the list of arguements from standard input and stores it
 in a struct string array.
*/
strar getArgs();

/*
OPTIONS
This function gets the flags and handles the options. It changes the variables
in accordance with the choice of the user.

com - a command we got from launchin the executable

*/
void getOptions(strar *com, flags* flag);

/*
CONSTRUCT COMMAND
We constrcut a command from the arguments of the executable and the ones we got
from stdin.

com - new command
inp - string array from stdin
exec - arguements passed to executable
maxArgs - maximum number of arguments
*/
void constrCom(strar *com,strar *inp, strar *exec, int maxArgs);

/*
EXECUTE COMMAND IN PARALLEL
inp - string array from stdin
exec - arguements passed to executable
flag - flags from input
*/
void executePar(strar* inp, strar* exec, flags* flag);
#endif