#include "../headers/ProcessFetcher.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#define UID getuid()
static DIR *dirp;

int countFiles();

int main(int argc, char** argv) {
  printf("%d\n", countFiles());
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
  DIR *d = opendir("/proc");
  struct dirent *curr = malloc(sizeof(struct dirent));
  int count = 0;

  while ( (curr = readdir(d)) ) {
    if (atoi(curr->d_name)) {
      printf("%d\n", atoi(curr->d_name));
      count++;
    }
  }

  return count;
}