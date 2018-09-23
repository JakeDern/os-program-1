#ifndef _PROCESSFETCHER
#define _PROCESSFETCHER

typedef struct Process {
  int pid;
  char state;
  char *userTime;
  char *sysTime;
  char *numPages;
  char *cmdLine;
} Process;

typedef struct ProcessNode {
  Process *Process;
  struct ProcessNode *next;
} ProcessNode;

extern Process * getProcess(int pid);

extern ProcessNode * getAllProccesses();
#endif