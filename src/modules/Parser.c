#include "../headers/Parser.h"
#include "../headers/ProcessFetcher.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#define PID_LENGTH 5
#define BIG_NUM 15
#define STATE_INDEX 3
#define UTIME_INDEX 14
#define STIME_INDEX 15
#define BASE "/proc/"

int parseStat(Process *p, char *path);
int parseStatM(Process *p, char *path);
int parseCmd(Process *p, char *path);
void freeFields(Process *p);

// int main(int argc, char **argv) {
//   parseInfo(4215);
// }

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
    return NULL;  
  }

  // parseCmd(ret, cmdPath);
  // parseStat(ret, statPath);
  // parseStatM(ret, statMPath);

  // free mem
  free(statPath);
  free(statMPath);
  free(cmdPath);
  free(base);

  // printf("command line: %s\n", ret->cmdLine);

  return ret;
}

int parseStat(Process *p, char* path) {
  // set up buffer and file
  FILE *stat;
  if ((stat = fopen(path, "r")) == NULL) {
    return 1;
  }

  //TODO make this a constant
  char *curr = malloc(50);
  char *lineBuff = malloc(sizeof(char) * 1000 + 1);
  fgets(lineBuff, 1000, stat);

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

int parseStatM(Process *p, char* path) {
  // set up buffer and file
  FILE *statM;
  if ((statM = fopen(path, "r")) == NULL) {
    return 1;
  }

  char *buffer = malloc(1000);
  fgets(buffer, 1000, statM);
  char *size = malloc(BIG_NUM + 1);

  // scan first line from file
  sscanf(buffer, "%s", size);

  // record size
  p->numPages = malloc(sizeof(size));
  p->numPages = strcpy(p->numPages, size);

  // free mem and close resources
  free(size);
  free(buffer);
  fclose(statM);

  return 0;
} 

int parseCmd(Process *p, char* path) {
  FILE *cmd;
  if ((cmd = fopen(path, "r")) == NULL) {
    return 1;
  }

  //TODO fix these to use constants
  char buffer[3000];
  char buffer2[1000];
  // printf("buffer size after malloc: %lu\n", sizeof(buffer));

  while((fgets(buffer2, 1000, cmd)) != NULL) {
    strcat(buffer, buffer2);
  }
  
  p->cmdLine = calloc(1, 3000);
  strcpy(p->cmdLine, buffer);
  memset(buffer, 0, 3000);
  memset(buffer2, 0, 1000);

  fclose(cmd);
  // free(buffer);
  // free(buffer2);
  // printf("buffer size when done: %lu\n", sizeof(buffer));
  // printf("struct cmd size: %lu\n", sizeof(p->cmdLine));
  return 0;
} 

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
