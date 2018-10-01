/**
 * @author Jake Dern
 * @author Alex Dallman
 **/

#include "../headers/Parser.h"
#include "../headers/ProcessFetcher.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#define PID_LENGTH 5    // length of a pid
#define BIG_NUM 15      // max expected number length
#define STATE_INDEX 3   // index of state info in stat
#define UTIME_INDEX 14  // index of usertime info in stat
#define STIME_INDEX 15  // index of systime info in stat
#define FILE_BUFFER 1000// buffer for copying from files
#define COPY_BUF 50     // buffer for copying between strings
#define BASE "/proc/"   // base of all needed file paths

// forward declarations
int parseStat(Process *p, char *path);
int parseStatM(Process *p, char *path);
int parseCmd(Process *p, char *path);
void freeFields(Process *p);

/** @override */
Process * parseInfo(int pid) {
  // construct base file path for needed files
  char *base = malloc((sizeof(char) * PID_LENGTH) + sizeof(BASE));
  char strID[PID_LENGTH + 1];
  sprintf(strID, "%d", pid);
  strcpy(base, "/proc/");
  strcat(base, strID);

  // create paths for relevant files
  char *statPath = malloc(sizeof(BASE) + sizeof(PID_LENGTH) + sizeof("/stat") + 1);
  char *statMPath = malloc(sizeof(BASE) + sizeof(PID_LENGTH) + sizeof("/statm") + 1);
  char *cmdPath = malloc(sizeof(BASE) +  sizeof(PID_LENGTH) +sizeof("/cmdline") + 1);

  strcpy(statPath, base);
  strcpy(statMPath, base);
  strcpy(cmdPath, base);

  strcat(statPath, "/stat");
  strcat(statMPath, "/statm");
  strcat(cmdPath, "/cmdline");

  // create return struct
  Process *ret = malloc(sizeof(Process));
    ret->userTime = NULL;
    ret->sysTime = NULL;
    ret->cmdLine = NULL;
    ret->numPages = NULL;
    ret->pid = pid;

  // parse needed info
  if ( parseStat(ret, statPath) || parseCmd(ret, cmdPath) || parseStatM(ret, statMPath)) {
    printf("PARSING FAILED: %d\n", pid);
    freeFields(ret);

    free(statPath);
    free(statMPath);
    free(cmdPath);
    free(base);
    
    return NULL;  
  }

  // free mem
  free(statPath);
  free(statMPath);
  free(cmdPath);
  free(base);

  return ret;
}

/**
 * Parses state, usertime, and system time
 * information about a process from the stat
 * file in the /proc/pid directory, and puts this
 * information directly into the provided struct
 * 
 * @param path path to the relevant stat file
 * @param p the process to store the information in
 * @returns 0 iff successful, 1 otherwise
 **/
int parseStat(Process *p, char* path) {
  // set up buffer and file
  FILE *stat;
  if ((stat = fopen(path, "r")) == NULL) {
    return 1;
  }

  //TODO make this a constant
  char *curr = malloc(COPY_BUF);
  char *lineBuff = malloc(FILE_BUFFER + 1);
  fgets(lineBuff, FILE_BUFFER, stat);

  // traverse file, pulling out relevant information
  char *currPos = lineBuff;
  for ( int i = 1; i <= 15; i++) {
    sscanf(currPos, "%s", curr);
    currPos += strlen(curr) + 1;
    switch(i) {
      case STATE_INDEX: {
        p->state = *curr;
        break;
      }
      case UTIME_INDEX: {
        p->userTime = malloc(BIG_NUM + 1);
        strcpy(p->userTime, curr);
        break;
      }
      case STIME_INDEX: {
        p->sysTime = malloc(BIG_NUM + 1);
        strcpy(p->sysTime, curr);
        break;
      }
    }
  }

  // free mem and close resources
  free(curr);
  free(lineBuff);
  fclose(stat);

  return 0;
} 

/**
 * Parses memory usage information in pages
 * about a process from the statM
 * file in the /proc/pid directory, and puts this
 * information directly into the provided struct
 * 
 * @param path path to the relevant statM file
 * @param p the process to store the information in
 * @returns 0 iff successful, 1 otherwise
 **/
int parseStatM(Process *p, char* path) {
  // set up buffer and file
  FILE *statM;
  if ((statM = fopen(path, "r")) == NULL) {
    return 1;
  }

  // setup buffers for file reading
  char *buffer = malloc(FILE_BUFFER);
  fgets(buffer, FILE_BUFFER, statM);
  char *size = malloc(BIG_NUM + 1);

  // scan first line from file
  sscanf(buffer, "%s", size);

  // record size
  p->numPages = malloc(BIG_NUM + 1);
  p->numPages = strcpy(p->numPages, size);

  // free mem and close resources
  free(size);
  free(buffer);
  fclose(statM);

  return 0;
} 

/**
 * Parses about the command line command that
 * started this process from the cmdline
 * file in the /proc/pid directory, and puts this
 * information directly into the provided struct
 * 
 * @param path path to the relevant cmdline file
 * @param p the process to store the information in
 * @returns 0 iff successful, 1 otherwise
 **/
int parseCmd(Process *p, char* path) {
  FILE *cmd;
  if ((cmd = fopen(path, "r")) == NULL) {
    return 1;
  }

  // buffers for reading sections of cmdline
  // storing/concatenating all sections
  char buffer[FILE_BUFFER * 3];
  char buffer2[FILE_BUFFER];

  // copy contents of cmdline
  while((fgets(buffer2, FILE_BUFFER, cmd)) != NULL) {
    strcat(buffer, buffer2);
  }
  
  // copy cmdline into the struct 
  p->cmdLine = calloc(1, FILE_BUFFER * 3);
  strcpy(p->cmdLine, buffer);

  // hacky fixes bug for some reason
  memset(buffer, 0, FILE_BUFFER * 3);
  memset(buffer2, 0, FILE_BUFFER);

  // close resources
  fclose(cmd);
  return 0;
} 

/**
 * Frees all memory associated with a Process struct
 **/
void freeFields(Process *p) {
  if(p->userTime) {
    free(p->userTime);
  }
  if(p->sysTime) {
    free(p->sysTime);
  }
  if(p->cmdLine) {
    free(p->cmdLine);
  }
  if(p->numPages) {
    free(p->numPages);
  }
  free(p);
}
