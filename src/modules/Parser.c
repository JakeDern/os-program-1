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

int parseStat(Process *p, char *path);
int parseStatM(Process *p, char *path);
int parseCmd(Process *p, char *path);

int main(int argc, char **argv) {
  parseInfo(4215);
}

Process * parseInfo(int pid) {
  // construct base file path for needed files
  char *base = malloc((sizeof(char) * PID_LENGTH) + sizeof("/proc/"));
  char strID[PID_LENGTH + 1];
  sprintf(strID, "%d", pid);
  strcpy(base, "/proc/");
  strcat(base, strID);

  // create paths for relevant files
  char *statPath = malloc(sizeof(base) + sizeof("/stat"));
  char *statMPath = malloc(sizeof(base) + sizeof("/statm"));
  char *cmdPath = malloc(sizeof(base) + sizeof("/cmdline"));

  strcpy(statPath, base);
  strcpy(statMPath, base);
  strcpy(cmdPath, base);

  strcat(statPath, "/stat");
  strcat(statMPath, "/statm");
  strcat(cmdPath, "/cmdline");

  Process *ret = malloc(sizeof(Process));
  ret->pid = pid;

  parseCmd(ret, cmdPath);
  parseStat(ret, statPath);

  printf("%d\n", ret->pid);
  printf("%c\n", ret->state);
  printf("%s\n", ret->sysTime);
  fflush(stdout);
  printf("%s\n", ret->userTime);
    

  return NULL;
}

int parseStat(Process *p, char* path) {
  FILE *stat = fopen(path, "r");
  char *curr = malloc(sizeof(char) * BIG_NUM);
  char *lineBuff= malloc(sizeof(char) * 1000);
  fgets(lineBuff, 1000, stat);
  
  for ( int i = 1; i <= 15; i++) {
    sscanf(lineBuff, "%s", curr);
    lineBuff += strlen(curr) + 1;
    switch(i) {
      case STATE_INDEX: {
        p->state = *curr;
        break;
      }
      case UTIME_INDEX: {
        p->userTime = malloc(sizeof(curr));
        strcpy(p->userTime, curr);
        break;
      }
      case STIME_INDEX: {
        p->sysTime = malloc(sizeof(curr));
        strcpy(p->sysTime, curr);
        break;
      }
    }
  }

  return 0;
} 

int parseStatM(Process *p, char* path) {
  return 0;
} 

int parseCmd(Process *p, char* path) {
  FILE *cmd = fopen(path, "r");
  char *buffer = malloc(sizeof(char) * 1000);
  char *buffer2 = malloc(sizeof(char) * 1000);

  while(fgets(buffer2, 1000, cmd)) {
    strcat(buffer, buffer2);
  }
  
  // free(buffer2);

  p->cmdLine = buffer;
  return 0;
} 
