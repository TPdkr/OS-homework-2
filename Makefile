#this was done by Timofei Podkorytov
#for assignment 2 for Operating Systems course
#fall 2024
all: xargs.c strar.c func.c
	gcc -Wall -o xargs xargs.c strar.c func.c
