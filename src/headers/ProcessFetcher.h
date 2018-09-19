typedef struct ProcessInfo {
  int pid;
  char state;
  char *userTime;
  char *sysTime;
  int numPages;
  char *cmdLine;
} ProcessInfo;

int getProcess(int pid, ProcessInfo *p);

ProcessInfo * getAllProccesses();