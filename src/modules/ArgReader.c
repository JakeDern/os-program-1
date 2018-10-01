/**
 * @author Jake Dern
 * @author Alex Dallman
 **/

#include "../headers/ArgReader.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define USAGE_ERROR "Usage error: valid arguments are -p <pid> | -s(-) | -U(-) | -S(-) | -v(-) | -c(-) in any order, each used only once"
#define COMMAND_FORMAT_ERROR "Command format error: all command line arguments must be prefaced with a '-'"
#define DUPLICATE_FLAG_ERROR "Duplicate argument error: duplicate arguments are not valid input"
#define BAD_PID_INPUT_ERROR "Bad pid input error: pid must be a natural number below 32768"
#define DEFUALT_sFLAG 0
#define DEFUALT_UFLAG 1
#define DEFAULT_SFLAG 0
#define DEFAULT_vFLAG 0
#define DEFAULT_cFLAG 1



char* errMsg;

/** @override */ 
Options * getOpts(int argc, char **argv) {

  //expected args is to check for gibberish arguments
  int expectedArgs = 0;
  char command;

  Options *opts = malloc(sizeof(Options));
    opts->pFlag = -1;
    opts->sFlag = -1;
    opts->UFlag = -1;
    opts->SFlag = -1;
    opts->vFlag = -1;
    opts->cFlag = -1;

  while ((command = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
    expectedArgs++;
    switch (command) {
      case 'p': {
        if (opts->pFlag == -1) { // check if this is the first time the -p flag has come up
          if (atoi(optarg)) { // check if the -p arg is a number
            opts->pFlag = atoi(optarg);
            if (opts->pFlag < 0) { // check if the pid given is less than 0
              errMsg = BAD_PID_INPUT_ERROR;
              free(opts);
              return NULL;
            }
          } else if (*optarg == '0') { // special case because 0 returns false in above if statement but is a valid pid
            opts->pFlag = 0;
          } else {
            errMsg = BAD_PID_INPUT_ERROR;
            free(opts);
            return NULL;
          }
          expectedArgs++;
       }
       break;
      }
	/*
	 *the rest of logic for the argreader goes as follows
	 *check for a duplicate argument
	 *check for a '-' following the command to disable the command
	 *make sure there is no bad input after the command
	 *mark the flag in the struct as a 1 or a 0 depending on input command (used to print certain info)
	 */
      case 's': {
        if (opts->sFlag == -1) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->sFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
               free(opts);
               return NULL;
             }
           }
           else {
             //-s case
             opts->sFlag = 1;
           }
        }
        else {
          //duplicate flag error
          errMsg = DUPLICATE_FLAG_ERROR;
          free(opts);
          return NULL;
        }
        break;
      }
      case 'U': {
        if (opts->UFlag == -1) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->UFlag = 0;
             }
             else {
               errMsg = USAGE_ERROR;
               free(opts);
               return NULL;
             }
           }
           else {
             //-s case
             opts->UFlag = 1;
           }
        }
        else {
          errMsg = DUPLICATE_FLAG_ERROR;
          free(opts);
          return NULL;
          //duplicate flag error
        }
        break;
      }
      case 'S': {
        if (opts->SFlag == -1) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->SFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
               free(opts);
               return NULL;
             }
           }
           else {
             //-s case
             opts->SFlag = 1;
           }
        }
        else {
          errMsg = DUPLICATE_FLAG_ERROR;
          //duplicate flag error
        }
        break;
      }
      case 'v': {
        if (opts->vFlag == -1) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->vFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
               free(opts);
               return NULL;
             }
           }
           else {
             //-s case
             opts->vFlag = 1;
           }
        }
        else {
          errMsg = DUPLICATE_FLAG_ERROR;
          free(opts);
          return NULL;
          //duplicate flag error
        }
        break;
      }
      case 'c': {
       if (opts->cFlag == -1) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->cFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
               free(opts);
               return NULL;
             }
           }
           else {
             opts->cFlag = 1;
           }
        }
        else {
          //duplicate flag error
          errMsg = DUPLICATE_FLAG_ERROR;
          free(opts);
          return NULL;
        }
        break;
      }
      case '?': {
        errMsg = USAGE_ERROR;
        free(opts);
        return NULL;
      }
      default: {
	//should never be reached
        free(opts);
        return NULL;
      }
    }
  }

  // verify there were not any nonsensical arguments in the cmd line
  if (expectedArgs + 1 != argc) {
    errMsg = COMMAND_FORMAT_ERROR;
    free(opts);
    return NULL;
  }

  // set all untouched flags to the default per program specs
  if(opts->sFlag == -1) opts->sFlag = DEFUALT_sFLAG;
  if(opts->UFlag == -1) opts->UFlag = DEFUALT_UFLAG;
  if(opts->SFlag == -1) opts->SFlag = DEFAULT_SFLAG;
  if(opts->vFlag == -1) opts->vFlag = DEFAULT_vFLAG;
  if(opts->cFlag == -1) opts->cFlag = DEFAULT_cFLAG;

return opts;

}
