#ifndef _PROCESSFETCHER
#define _PROCESSFETCHER

/*
 * Process struct contains all the relevant information relating to an individual process
 */
typedef struct Process {
  int pid;
  char state;
  char *userTime;
  char *sysTime;
  char *numPages;
  char *cmdLine;
} Process;

/*
 * getProcess returns a Process structure with all relevant information about the process
 *
 *@param pid is the process ID needed to find an individual process
 *@return Process is the process that was found with that PID
 *@return NULL if the process was not found in the /proc found in the folder
 *
 */
extern Process * getProcess(int pid);

/*
 *getAllProcesses will successively return processes that the user owns within the /proc directory
 *
 *@return Process is the current process being viewed within the /proc directory (owned)
 *@return NULL after there are no more processes to be gathered
 *
 */
extern Process * getAllProcesses();
#endif
