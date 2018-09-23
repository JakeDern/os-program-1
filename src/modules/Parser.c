#include "../headers/Parser.h"
#include "../headers/ProcessFetcher.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#define PID_LENGTH 5

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
  
  parseCmd(ret, cmdPath);

  return NULL;
}

int parseStat(Process *p, char* path) {
  FILE *stat = fopen(path, "r");
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
    printf("%s\n", buffer2);
    strcat(buffer, buffer2);
  }

  // for (int i = 0; i < 1000; i++) {
  //   printf("%c", *(buffer + i));
  // }
  // printf("\n");

  // fgets(buffer, 1000, cmd);
  // sscanf(buffer, "%s", buffer);

  printf("%s\n", buffer);
  printf("%d\n", cmd == NULL);
  return 0;
} 
