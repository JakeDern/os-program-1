#include "./headers/Parser.h"
#include "./headers/ProcessFetcher.h"
#include "./headers/ArgReader.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

int main(int argc, char **argv) {
  printf("I compiled\n");
  Process *p = getProcess(2029);
  printf("%d\n", p->pid);
}