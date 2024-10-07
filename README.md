# Assignment 2
## Submitted by Timofei Podkorytov
for operating systems course in fall 2024

## Compiling: Makefile
The following make commands are available:
```
$ make all
```
This compiles all files into xargs executable that accepts user input.
## Running:
Runs the main function of the code.

```./xargs```

## Files:
- Makefile
- README.md
- xargs.c
- flags.h
- func.h
- func.c
- strar.h
- strar.c

Makefile provides make commands. README gives the description of the 
homework submission.

The file xargs.c has the main function, where all the other function calls
are made.Firstly, input and options are taken and then the corresponding actions are taken

Flags give is a way to store data from flags that are passed to us.

Func stores useful and essential functions for execution of the code.

Strar is a string array, it allows us a nicer way to pass arrays of strings arguments and to process them.
