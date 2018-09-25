#include "../headers/ProcessFetcher.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define UID getuid()
#define COPY_BUFFER 50
#define PATH_LENGTH 15
static DIR *dirp = NULL;

int countFiles();
int fileOwned(int pid);
char * buildPath(int pid);

// int main(int argc, char** argv) {
//   getProcess(1447);
//   return 0;
// }

Process * getProcess(int pid) {
  Process *p = malloc(sizeof(struct Process));
  char *fileName = buildPath(pid);
  
  p = parseInfo(pid);

  return p;
}

ProcessNode * getAllProcesses() {
  // if directory iteration not in progess, open new one
  if (!dirp) {
    dirp = opendir("/proc");
  }
  struct dirent *currDirectory = malloc(sizeof(struct dirent));

  // read one more file if available
  if (currDirectory = readdir(dirp)) {
    if (atoi(currDirectory->d_name)) {
      Process *nextProcess = parseInfo(currDirectory->d_name);
      return nextProcess;
    }
  }

  return NULL;
}

int fileOwned(int pid) {
  // construct path to status file
  char *path = buildPath(pid);
  char *status = "/status";
  char *statusPath = malloc(sizeof(char) * COPY_BUFFER);
  statusPath = strcat(path, status);

  // open file and create container for lines
  FILE *fptr = fopen(statusPath, "r");
  char *line = malloc(sizeof(char) * COPY_BUFFER);

  //traverse to line containing owner id
  for (int i = 0 ; i < 10; i++) {
    fgets(line, COPY_BUFFER, fptr);
  }

  //parse owner id
  int owner = 0;
  sscanf(line, "%s %d", path, &owner);

  // free memory
  free(statusPath);
  free(line);

  return owner == UID;

}

char * buildPath(int pid) {
  char strID[COPY_BUFFER];
  sprintf(strID, "%d", pid);
  char base[] = "/proc/";
  char *fileName = malloc(sizeof(char) * PATH_LENGTH);
  
  strcpy(fileName, strcat(base, strID));

  return fileName;
}

int countFiles() {
  DIR *d = opendir("/proc");
  struct dirent *curr = malloc(sizeof(struct dirent));
  int count = 0;

  while ((curr = readdir(d))) {
    if (atoi(curr->d_name)) {
      printf("%d\n", atoi(curr->d_name));
      count++;
    }
  }

  return count;
}