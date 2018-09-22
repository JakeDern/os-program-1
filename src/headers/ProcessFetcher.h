#ifndef _PROCESSFETCHER
#define _PROCESSFETCHER

typedef struct ProcessNode {
  Process *Process;
  ProcessNode *next;
} ProcessNode;

typedef struct Process {
  int pid;
  char state;
  char *userTime;
  char *sysTime;
  int numPages;
  char *cmdLine;
} Process;

extern Process * getProcess(int pid);

extern ProcessNode * getAllProccesses();
#endif