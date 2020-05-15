#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct process {
  int pid;
  int arrivalTime, lifeTime; //line2
  int memPieces, memReq; //line 3. if there are multiple address spaces, add multiple numbers to total memSize sum.
  //example: if memPieces = 2, then memSize is the next two numbers added up. 2 200 400
};

struct memPage {
	int pageStart, pageEnd, _pid, pageNum, arrivalTime, endTime;
};

void getInputQueue(queue<process> _inputQueue) {
  cout << "Input Queue:[";
  while (!_inputQueue.empty()) {
    cout << _inputQueue.front().pid << " ";
    _inputQueue.pop();
  }
  cout << "]" << endl;
} 


int main(/*int argc, char *argv[]*/) {

  long int memSize = 0;
  long int pageSize = 0;
  char filename;
  FILE * inputFile;
  size_t result;
  long int virtualClock = 0;
  char numProcess;

  // creating an empty queue
  queue<process> inputQueue, waitQueue;

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
  switch (pageSize) {
    case 1:
      pageSize = 100;
      break;
    case 2:
      pageSize = 200;
      break;
    case 3:
      pageSize = 400;
      break;
  }

  //Get the number of free pages
  int freePages = memSize / pageSize;

  // prompt user for the name of the workload file
  fprintf(stderr, "Please enter the name of the workload file: ");
  scanf("%s", &filename);

  /*
      The file should contain theint count = 0; following (will be listed sequentially)
      - int value N -> # of processes in file
      - 1st line: unique process identifier (PID)
      - 2nd line: time submitted (arrival time) to system
          --> lifetime after submission to main memory (lifetime in memory)
      - 3rd line: memory requirements (address space)
          --> NOTE: this is a sequence of >= 1 integers
              - 1st int: # of 'pieces' https://youtu.be/uHUDpQfMe1kof memory on the line
              - Following #'s denote the address spaces
                  --> totalling these ints to get the overall space requirements
  */

  // opening the file
  //inputFile = fopen(&filename, "r");
  ifstream inputFile;
  inputFile.open(filename);
  if (!inputFile) {
    perror("Error reading file.");
    exit(-1);
  }


  // check to see if we opened the file sucessfully
  //if(!inputFile) {
      //perror("Error");
      //exit(-1);
  //}


  // need to load the entire address space of the process to main memory for execution

  // need a virtual clock (int or long) that we can increment until the simulation completes or == 100,000

  // need to store processes in an input queue

  // have some kind of loop (perhaps while loop) to check the memory space and allocate the head of the input queue

   // read the number of processes - change later
      result = fread(&numProcess, 1, 1, inputFile);

  // check to make sure we read the number of processes correctly
  if (result != 1){
      fputs("Reading number of processes error\n", stderr);
      exit(-1);
  }
  fprintf(stderr, "%c\n", numProcess);

  for (int i = 0; x < numProcess; x++) { //will this loop go into the virtualclock loop?

    //get pId of inputQueue[i] and error check
    //get arrival time and life time of inputQueue[i] and error check
    //get the address space first of inputQueue[i] and error check
    //read in the number for address space.
    //int total = 0;

    process tempProcess;

    //get id
    //inputFile >> waitQueue[i].pid;
    inputFile >> tempProcess.pid;
    if (inputFile.fail()) {
      perror("Error reading process id (line 1).");
      exit(-1);
    }

    //inputFile >> waitQueue[i].arrivalTime >> waitQueue[i].lifeTime;
    inputFile >> tempProcess.arrivalTime >> tempProcess.lifeTime;
    if (inputFile.fail()) {
      perror("Error reading times (line 2).");
      exit(-1);
    }

    //inputFile >> waitQueue[i].memPieces;
    inputFile >> tempProcess.memPieces;
    if (inputFile.fail()) {
      perror("Error reading address space (line 3).");
      exit(-1);
    }

    int total = 0;
    int temp = 0; //pieces of memSize
    for (int j = 0; j < tempProcess.memPieces; j++) {
      inputFile >> temp; //Read in first value for memSize
      total += temp;
    }
    tempProcess.memReq = total;
    waitQueue.push(tempProcess); 
    }


    //Memory map implementation.
    memPage begin;
    vector<memPage> memoryMap;
    for (int k = 0; k < freePages; k++){
      begin.pageStart = k * pageSize;
      begin.pageEnd = ((k + 1) * pageSize) - 1;
      begin.pageNum = 0;
      begin._pid = -1;
      begin.endTime = -1;
      memoryMap.push_back(begin); //Push to the memory map
    }

    int timeLimit = 100000;

    while (virtualClock != timeLimit) {
      bool print = true;
      bool waitTest = false;
      bool printMap = false;
      process frontP = waitQueue.front();

      //Gets processes at time, adds to queue
      if (!waitQueue.empty()) 
      {       
        waitTest = (frontP.arrivalTime == virtualClock) //Check to see if the arrival time of a processmatches the current time
        //If it does, go through
      }

      while (waitTest == true)
      {
        cout << "t= " << virtualClock << endl;
        cout << "Process " << frontP.pid << " arrives".
        inputQueue.push(frontP); //Push onto input queue
        waitQueue.pop(); //Remove from waiting queue
        getInputQueue(inputQueue);
        printMap = true;
        print = false;
        if (!waitQueue.empty()) {
          waitTest = (frontP.arrivalTime == virtualClock); //Repeat loop if not empty
        }
        else { //if it is empty, leave the loop
          waitTest = false;
        }
      }
      bool pprint = true;
    }



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




  return 0;

}
