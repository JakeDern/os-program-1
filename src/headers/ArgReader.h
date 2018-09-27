/**
 * @author Jake Dern
 * @author Alex Dallman
 **/

#ifndef _ARGREADER
#define _ARGREADER

/*
 *in the event that getOpts returns NULL, this field will contain an error message hinting at why the program may have errored.
 */
extern char* errMsg;

/*
 *this struct will be used to represent which items are and are not to be printed in the output along with the PID
 */
typedef struct Options {
  int pFlag;
  int sFlag;
  int UFlag;
  int SFlag;
  int vFlag;
  int cFlag;
} Options;


/*
 *getOpts is a method to parse all user commands for the 537ps program.
 *getOpts sorts through the input to verify which commands are used and aids in instructing the user how to use 537ps if
 *there is incorrect usage.
 *
 *@param argc is the number of command line arguments used to start 537ps
 *@param argv is the char * array that contains all command line arguments inputed by the user
 *
 * @return an Options struct containing flags indicating whether certain fields are to be displayed about a proc.
 * @return NULL if there is any invalid input to the command line along with assigning an errMsg to extern char * errMsg.
 */
extern Options * getOpts(int argc, char **argv);
#endif
