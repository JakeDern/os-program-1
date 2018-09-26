#include "../headers/ProcessFetcher.h"
#include "../headers/Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define UID getuid()
#define COPY_BUFFER 50
#define PATH_LENGTH 15
#define PID_LENGTH 6
#define READ_BUFFER 1000
static DIR *dirp = NULL;

int countFiles();
int fileOwned(int pid);
char * buildPath(int pid);

Process * getProcess(int pid) {
  if (fileOwned(pid)) {
    return parseInfo(pid);
  }
  return NULL;
}

Process * getAllProcesses() {
  // if directory iteration not in progess, open new one
  if (!dirp) {
    dirp = opendir("/proc");
  }
  struct dirent *currDirectory;

  // read one more file if available
  while((currDirectory = readdir(dirp))) {
    if (atoi(currDirectory->d_name)) {
      if(fileOwned(atoi(currDirectory->d_name))) {
         break;
      }
    }
  }

  if (currDirectory) {
    Process *p = parseInfo(atoi(currDirectory->d_name));
    if (!p) {
      return NULL;
    } 
    return p;
  }

  closedir(dirp);
  return NULL;
}

int fileOwned(int pid) {
  // construct path to status file
  char *path = buildPath(pid);
  char *status = "/status";
  char *statusPath = malloc(COPY_BUFFER);
  statusPath = strcpy(statusPath, strcat(path, status));

  // open file and create container for lines
  FILE *fptr;
  if ((fptr = fopen(statusPath, "r")) == NULL) {
    free(fptr);
    return 0;
  }
  char *line = malloc(READ_BUFFER);

  // traverse to line containing owner id
  for (int i = 0 ; i < 10; i++) {
    fgets(line, 1000, fptr);
  }

  // parse owner id
  int owner = 0;
  sscanf(line, "%s %d", path, &owner);

  // free memory and close resources
  free(statusPath);
  free(line);
  free(path);
  fclose(fptr);

  return ((uint) owner) == UID;

}

char * buildPath(int pid) {
  //TODO figure out if this needs to be freed
  char strID[PID_LENGTH];
  sprintf(strID, "%d", pid);
  char fileName[COPY_BUFFER];

  strcpy(fileName, "/proc/");
  strcat(fileName, strID);
  
  char *ret = malloc(sizeof(fileName) + 1);
  strcpy(ret, fileName);
  return ret;
}
