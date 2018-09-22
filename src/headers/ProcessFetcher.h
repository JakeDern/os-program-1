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

extern int getProcess(int pid, Process * p);

extern ProcessNode * getAllProccesses();
#endif