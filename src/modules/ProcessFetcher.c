/**
 * @author Jake Dern
 * @author Alex Dallman
 **/

#include "../headers/ProcessFetcher.h"
#include "../headers/Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define UID getuid()    // current users UID
#define COPY_BUFFER 50  // buffer for copying strings
#define PATH_LENGTH 15  // max file path length for /proc/<pid>
#define PID_LENGTH 6    // max size of a string for a pid
#define READ_BUFFER 1000// read buffer for reading from a file

static DIR *dirp = NULL;//holds state for traversing directory

int countFiles();
int fileOwned(int pid);
char * buildPath(int pid);

/** @override */
Process * getProcess(int pid) {
  // check ownership and return process if owned
  if (fileOwned(pid)) {
    return parseInfo(pid);
  }
  return NULL;
}

/** @override */
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

  // verify a file was found and return corresponding process
  if (currDirectory) {
    Process *p = parseInfo(atoi(currDirectory->d_name));
    if (!p) {
      return NULL;
    } 
    return p;
  }

  // if the code made it here, the directory is done being
  // explored. Close resources and return NULL
  closedir(dirp);
  return NULL;
}

/**
 * Determines if a the file located at /proc/<pid>
 * is owned by the user running this process.
 * 
 * @param pid pid of the process to check
 * @return 1 iff the file is owned, 0 otherwise
 **/
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

  // traverse to line containing owner id
  char *line = malloc(READ_BUFFER);
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

/**
 * Constructs a path to the directory containing info
 * for the process with the specified pid. 
 * 
 * @param pid pid of the desired process
 * @return pointer to char array containing directory name
 **/
char * buildPath(int pid) {
  // parse the pid into a string
  char strID[PID_LENGTH];
  sprintf(strID, "%d", pid);
  char fileName[COPY_BUFFER];

  // construct the file path /proc/<pid>
  strcpy(fileName, "/proc/");
  strcat(fileName, strID);
  char *ret = malloc(sizeof(fileName) + 1);
  strcpy(ret, fileName);

  return ret;
}
