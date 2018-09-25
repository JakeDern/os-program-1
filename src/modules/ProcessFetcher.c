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
static DIR *dirp = NULL;

int countFiles();
int fileOwned(int pid);
char * buildPath(int pid);

// int main(int argc, char** argv) {
//   getProcess(1447);
//   return 0;
// }

Process * getProcess(int pid) {
  if (fileOwned(pid)) {
    return parseInfo(pid);
  }
  return NULL;
}

Process * getAllProcesses() {
  // if directory iteration not in progess, open new one
  if (!dirp) {
    // printf("init success\n");
    dirp = opendir("/proc");
  }
  struct dirent *currDirectory;

  // read one more file if available
  // printf("searching for next file\n");
  while((currDirectory = readdir(dirp))) {
    if (atoi(currDirectory->d_name)) {
      if(fileOwned(atoi(currDirectory->d_name))) {
         // printf("found next: %s\n", currDirectory->d_name);
         break;
      }
    }
  }

  if (currDirectory) {
    // printf("parsing: %s\n", currDirectory->d_name);
    Process *p = parseInfo(atoi(currDirectory->d_name));
    if (!p) {
      return NULL;
    } 
    // printf("finished parsing %d\n", atoi(currDirectory->d_name));
    return p;
  }

  closedir(dirp);
  // printf("last file found\n");
  return NULL;
}

int fileOwned(int pid) {
  // printf("checking ownership: %d\n", pid);
  // construct path to status file
  char *path = buildPath(pid);
  char *status = "/status";
  char *statusPath = malloc(sizeof(char) * COPY_BUFFER);
  statusPath = strcpy(statusPath, strcat(path, status));

  // open file and create container for lines
  // printf("opening file: %s\n", statusPath);
  FILE *fptr;

  if ((fptr = fopen(statusPath, "r")) == NULL) {
    free(fptr);
    return 0;
  }
  //TODO fix this buffer
  char *line = malloc(sizeof(char) * 1000);

  //traverse to line containing owner id
  // printf("traversing to location\n");
  for (int i = 0 ; i < 10; i++) {
    fgets(line, 1000, fptr);
  }

  //parse owner id
  // printf("scanning file\n");
  int owner = 0;
  sscanf(line, "%s %d", path, &owner);

  // free memory
  // printf("freeing mem\n");
  free(statusPath);
  free(line);
  free(path);
  fclose(fptr);

  // printf("finished ownership check: %d\n", pid);
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

// TODO delete this ffunc
int countFiles() {
  DIR *d = opendir("/proc");
  struct dirent *curr = malloc(sizeof(struct dirent));
  int count = 0;

  while ((curr = readdir(d))) {
    if (atoi(curr->d_name)) {
      if(fileOwned(atoi(curr->d_name))){
         printf("%d\n", atoi(curr->d_name));
         printf("print name\n");
        count++;
      }
    }
  }

  return count;
}