#ifndef _PARSER
#define _PARSER
#include "./ProcessFetcher.h"
#include <stdio.h>

/*
 * parseInfo gathers and returns all relevant info for a specific procecss in the form of a Process struct.
 *
 * @param pid is the process ID that the parser is to gather info on
 * @return Process is a process pointer to a structure containing all relevant process information
 * @return NULL if there was an error parsing this specific process
 *
 */
extern Process * parseInfo(int pid);

#endif
