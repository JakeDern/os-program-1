#include "./headers/Parser.h"
#include "./headers/ProcessFetcher.h"
#include "./headers/ArgReader.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

int main(int argc, char **argv) {
  Process *p = getProcess(2029);
  printf("pid: %d\n", p->pid);
  printf("cmd: %s\n", p->cmdLine);
  printf("state: %c\n", p->state);
  printf("sysTime: %s\n", p->sysTime);
  printf("userTime: %s\n", p->userTime);
  printf("numPages: %s\n", p->numPages);
}