typedef struct ProcessInfo {
  int pid;
  char state;
  char *userTime;
  char *sysTime;
  int pages;
  char *cmdLine;
} ProcessInfo;

int getProcess(int pid, ProcessInfo *p);

ProcessInfo * getAllProccesses();