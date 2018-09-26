#include "./headers/Parser.h"
#include "./headers/ProcessFetcher.h"
#include "./headers/ArgReader.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

void freeProcess(Process *p);
void printProcess(Options *opts, Process *p);
void printAllprocesses(Options *opts);

int main(int argc, char **argv) {
  Options *opts;
  if ((opts = getOpts(argc, argv)) == NULL) {
    printf("%s\n", errMsg);
    exit(1);
  }

  Process *p;
  if (opts->pFlag > -1) {
    if ((p = getProcess(opts->pFlag))) {
      printProcess(opts, p);
    } else {
      printf("Process ID: %d was not found.  Printing all processes.\n", opts->pFlag);
      printAllprocesses(opts);
    }
  } else {
    printAllprocesses(opts);
  }
}

  
  
  // if(p = getProcess(4215)) {
  //   printf("pid: %d, state: %c sysTime: %s userTime: %s numPages: %s\n", 
  //   p->pid, p->state, p->sysTime, p->userTime, p->numPages);
  //   freeProcess(p);
  // }

  // while((p = getAllProcesses())) {
  //   printf("pid: %d, state: %c sysTime: %s userTime: %s numPages: %s\n", 
  //   p->pid, p->state, p->sysTime, p->userTime, p->numPages);
  //   freeProcess(p);
  // }
    // printf("pid: %d, state: %c sysTime: %s userTime: %s numPages: %s\n", 
    // p->pid, p->state, p->sysTime, p->userTime, p->numPages);
  // printf("cmd: %s\n", p->cmdLine);
  // printf("state: %c\n", p->state);
  // printf("sysTime: %s\n", p->sysTime);
  // printf("userTime: %s\n", p->userTime);
  // printf("numPages: %s\n", p->numPages);


void printProcess(Options *opts, Process *p) {
  printf("%d: ", p->pid);
  if (opts->sFlag) {
    printf("%c ", p->state);
  }
  if (opts->UFlag) {
    printf("utime=%s ", p->userTime);
  }
  if (opts->SFlag) {
    printf("systime=%s ", p->sysTime);
  }
  if (opts->vFlag) {
    printf("pages=%s ", p->numPages);
  }
  if (opts->cFlag) {
    printf("[ %s ] ", p->cmdLine);
  }
  printf("\n");
  fflush(stdout);
}

void printAllprocesses(Options *opts) {
  Process *p;
  while((p = getAllProcesses())) {
    printProcess(opts, p);
    freeProcess(p);
  }
}

void freeProcess(Process *p) {
  free(p->userTime);
  free(p->sysTime);
  //free(p->numPages);
  free(p->cmdLine);
  free(p);
}