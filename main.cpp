#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
using namespace std;


int main(/*int argc, char *argv[]*/) {
    
// prompt the user for a memory size; maximum size is 30,000

/*
    - display page sizes for the user to choose from
    - these should be multiples of page size
    - display three options
*/

// prompt user for the name of the workload file

/*
    The file should contain the following (will be listed sequentially)
    - int value N -> # of processes in file
    - 1st line: unique process identifier (PID)
    - 2nd line: time submitted (arrival time) to system
        --> lifetime after submission to main memory (lifetime in memory)
    - 3rd line: memory requirements (address space)
        --> NOTE: this is a sequence of >= 1 integers
            - 1st int: # of 'pieces' of memory on the line
            - Following #'s denote the address spaces
                --> totalling these ints to get the overall space requirements
*/

// opening the file

// need to load the entire address space of the process to main memory for execution

// need a virtual clock (int or long) that we can increment until the simulation completes or == 100,000

// need to store processes in an input queue

// have some kind of loop (perhaps while loop) to check the memory space and allocate the head of the input queue

/*
    here's we expect to happen within the loop:
    
    The Memory Manager (MM) will be invoked by the following checks:
    - if a new process arrives
        --> check the head of the input queue and see if we can allocate memory to it
        --> if yes, then allocate and repeat this process
    - if a process completes
        --> dellocate the space from that process
        --> compute its turnaround time
            --> difference between completion time and arrival time
            --> suggestion to store this in a data structure to later compute average turnaround time
        --> the MM will need to adjust the memory map to show newly freed space
            --> need to choose a convenient data structure to represent memory map

    - when we are allocating free space:
        --> always choose the lower end of memory to allocate

    - when writing to output file
        --> follow the format of the given out.txt(s)
*/


return 0;
} 
