#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <queue>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
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


int main() {

  long int memSize = 0;
  long int pageSize = 0;
  char filename;
  size_t result;
  long int virtualClock = 0;
  int numProcess;

  // creating an empty queue
  queue<process> inputQueue, waitQueue;
  process tempProcess;

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
  inputFile.open(&filename);
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

  // // read the number of processes - change later
  // result = fread(&numProcess, 1, 1, inputFile);

  // // check to make sure we read the number of processes correctly
  // if (result != 1){
  //     fputs("Reading number of processes error\n", stderr);
  //     exit(-1);
  // }

  inputFile >> numProcess;
  fprintf(stderr, "%d\n", numProcess);

  for (int i = 0; i < numProcess; i++) { //will this loop go into the virtualclock loop?

    //get pId of inputQueue[i] and error check
    //get arrival time and life time of inputQueue[i] and error check
    //get the address space first of inputQueue[i] and error check
    //read in the number for address space.
    //int total = 0;

    /*The Address Space line is a sequence of one or more integers separated by a single blank.
    The first integer gives the number of 'pieces' of memory on the line.
    This sequence denotes the total size of the address space of the process.
    You simply sum these integers to get the overall space requirement.*/
    //for (int j = 0; j < addrSpace; j++) loop through to add up all memory size nytes
    //{
        //read in first number for temp[j];
        //total += temp[j]
    //}
    //inputQueue[i].memSize = total;

    //get id
    inputFile >> tempProcess.pid;
    //waitQueue.push(process.pid);
    if (inputFile.fail()) {
      perror("Error reading process id (line 1).");
      exit(-1);
    }
    cout << tempProcess.pid << endl;

    //inputFile >> waitQueue.front().arrivalTime >> waitQueue.front().lifeTime;
    inputFile >> tempProcess.arrivalTime >> tempProcess.lifeTime;
    if (inputFile.fail()) {
      perror("Error reading times (line 2).");
      exit(-1);
    }
    cout << tempProcess.arrivalTime << " " << tempProcess.lifeTime << endl;
    // inputFile >> waitQueue.front().memPieces;
    inputFile >> tempProcess.memPieces;
    if (inputFile.fail()) {
      perror("Error reading address space (line 3).");
      exit(-1);
    }

    //cout << tempProcess.memPieces << "";

    int total = 0;
    int temp = 0; //pieces of memSize
    for (int j = 0; j < tempProcess.memPieces; j++) {
      inputFile >> temp; //Read in first value for memSize
      total += temp;
    }
    tempProcess.memReq = total;
    cout << tempProcess.memPieces << " " << tempProcess.memReq << endl;

    waitQueue.push(tempProcess);
  }
  
  int freePages = memSize/pageSize;
  vector<memPage> memoryMap;

  int maxTime = 100000;

  while(virtualClock != maxTime){
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

    // we need to clean out the pages that contained finished processes
    for (int i = 0; i < freePages; i++){
        int procDone = 0;

        // if a memory reaches its end time, remove it from the memory map
        if(memoryMap[i].endTime == virtualClock) {
            procDone = memoryMap[i]._pid;
            memoryMap[i]._pid = -1;
            memoryMap[i].pageNum = 0;
            memoryMap[i].endTime = 0;
            availablePages++;
        }
        
        // print out any processes that we are terminating
        if ((procDone != 0) && (pprint)) {
            if (print) {
              cout << "virtual clock = " << virtualClock << endl;
              print = false; 
            }
            cout << "\t\tProcess " << procDone << " completes\n";
            printMap = true;
            pprint = false;
        }
        
    }

    // let's see if there is any available pages of main memory to allocate to processes in the input queue
    while ((!inputQueue.empty()) && (availablePages >= inputQueue.front().memReq)) {
      if (print) {
        cout << "virtual clock = " << virtualClock << endl;
        print = false;
      }
      cout << "\t\tMM moves Process " << inputQueue.front().pid << " to memory\n";
      printMap = true;
      int endT = virtualClock + inputQueue.front().lifeTime;
      int pNum = 1;
      int i = 0;

      // if we reach the last process, we can set our maximum time to the end time of the process
      if (memoryMap[i]._pid == lastProcID) {
        maxTime = endT;
      }

      memoryMap[i].arrivalTime = inputQueue.front().arrivalTime;
      turnAroundTimes.push_back(memoryMap[i].endTime - memoryMap[i].arrivalTime);

      // execute this until our input queue is empty or until there are no more available pages
      while ((inputQueue.front().memReq != 0) && (i < freePages)) {
        // check to see if there is available memory in our memory map
        if (memoryMap[i]._pid == -1) {
          memoryMap[i]._pid = inputQueue.front().pid;
          memoryMap[i].pageNum = pNum;
          memoryMap[i].endTime = endT;
          pNum++
          availablePages--;
          inputQueue.front().memReq--;
        }
        i++;
      }
      inputQueue.pop();
    }
    
    // print our current memory map
    if(printMap) {
      printMemMap(memoryMap, freePages);
    }
     virtualClock++;
  }

  // calculate the average turnaround time
  int total = 0;
  for (int i = 0; i < turnAroundTimes.size(); i++) {
    total += turnAroundTimes[i];
  }
  double turnAround = total / turnAroundTimes.size();
  cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << turnAround << "\n" << endl;

  return 0;
}
