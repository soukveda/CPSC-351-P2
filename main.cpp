#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <queue>
using namespace std;


int main(/*int argc, char *argv[]*/) {

long int memSize = 0;
long int pageSize = 0;
char filename;
FILE * inputFile;
size_t result;
long int virtualClock = 0;
char numProcess;

// creating an empty queue
queue<int> inputQueue;
    
// prompt the user for a memory size; maximum size is 30,000
fprintf(stderr, "Please enter in a memory size (must be <= 30,000): ");
scanf("%ld", &memSize);

// check to see if the memory size is greater than 30,0000
if(memSize > 30000) {
    //perror("Error");
    fprintf(stderr, "The memory size is greater than the maximum size (30,000): %ld\n", memSize);
    exit(-1);
}

/*
    prompt the user for a page size:

    - display page sizes for the user to choose from
    - these should be multiples of memory size
    - display three options
*/
    
fprintf(stderr, "Please enter in a page size (1: 100, 2: 200, 3: 400): ");
scanf("%ld", &pageSize);

// check to see if the page size is valid
if(pageSize != 100 && pageSize != 200 && pageSize != 400 ) {
    fprintf(stderr, "The page size is invalid: %ld\n", pageSize);
    exit(-1);
}

// prompt user for the name of the workload file
fprintf(stderr, "Please enter the name of the workload file: ");
scanf("%s", &filename);

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
inputFile = fopen(&filename, "r");

// check to see if we opened the file sucessfully
if(!inputFile) {
    perror("Error");
    exit(-1);
}

// need to load the entire address space of the process to main memory for execution

// need a virtual clock (int or long) that we can increment until the simulation completes or == 100,000

// need to store processes in an input queue

// have some kind of loop (perhaps while loop) to check the memory space and allocate the head of the input queue

 // read the number of processes
    result = fread(&numProcess, 1, 1, inputFile);

// check to make sure we read the number of processes correctly
if (result != 1){
    fputs("Reading number of processes error\n", stderr);
    exit(-1);
}
fprintf(stderr, "%c\n", numProcess);

while(virtualClock <= 100,000){
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
                --> suggestion to store this in a data structure (or variable) to later compute average turnaround time
            --> the MM will need to adjust the memory map to show newly freed space
                --> need to choose a convenient data structure to represent memory map

        - when we are allocating free space:
            --> always choose the lower end of memory to allocate

        - when writing to output file
            --> follow the format of the given out.txt(s)
    */

   

   virtualClock++;
}



return 0;
} 
