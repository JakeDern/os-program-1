#include "../headers/ProcessFetcher.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#define UID getuid()

static DIR *dirp;

int main(int argc, char** argv) {
  printf("%d\n", UID);
  return 0;
}

Process * getProcess(int pid) {
  Process *p = malloc(sizeof(struct Process));
  return p;
}

ProcessNode * getAllProcesses() {
  return NULL;
}

int countFiles() {
  return 0;
}