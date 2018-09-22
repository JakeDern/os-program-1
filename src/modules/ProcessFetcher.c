#include "../headers/ProcessFetcher.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
  Process *p = getProcess(5);
}

Process * getProcess(int pid) {
  Process *p = malloc(sizeof(struct Process));
  return p;
}

ProcessNode * getAllProcesses() {
  return NULL;
}