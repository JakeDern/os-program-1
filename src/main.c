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
  // fetch options
  Options *opts;
  if ((opts = getOpts(argc, argv)) == NULL) {
    printf("%s\n", errMsg);
    exit(1);
  }

  // attempt to parse information about desired process(es)
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
  
  return 0;
}

/**
 * Prints information about the provided process according
 * to the options specified. 
 * 
 * @param p the process to print information about
 * @param opts options indicating desired information
 **/
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

/**
 * Prints information about all owned processes with
 * format according to provided options
 * 
 * @param opts indicating desired information
 **/
void printAllprocesses(Options *opts) {
  Process *p;
  while((p = getAllProcesses())) {
    printProcess(opts, p);
    freeProcess(p);
  }
}

/**
 * Frees all memory associated with a process
 * 
 * @param p the process to free
 **/
void freeProcess(Process *p) {
  free(p->userTime);
  free(p->sysTime);
  free(p->cmdLine);
  free(p);
}