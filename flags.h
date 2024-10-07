/*
This is assignment 2
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/

#ifndef FLAGS_H
#define FLAGS_H

/*
FLAG.H
STRUCT
Here i defined a trcut for storing flags that are passed

writeArg - do we need to print  before executing?
maxArgs - maxximum number of argumnets in command
par - parallel execution
*/
typedef struct flags{
    int writeArg;
    int maxArgs;
    int par;
} flags;

#endif