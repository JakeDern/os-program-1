#include "../headers/ArgReader.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define USAGE_ERROR "Usage error: valid arguments are -p | -s(-) | -U(-) | -S(-) | -v(-) | -c(-)"
#define COMMAND_FORMAT_ERROR "Command format error: all command line arguments must be prefaced with a '-'"
#define DUPLICATE_FLAG_ERROR "Duplicate argument error: duplicate arguments are not valid input"
#define BAD_PID_INPUT_ERROR "Bad pid input error: pid must be a natural number below 32768"

char* errMsg;

// int main(int argc, char **argv) {

// getOpts(argc, argv);


// return 0;

// }

Options * getOpts(int argc, char **argv) {


  int expectedArgs = 0;
  char command;

  Options *opts = malloc(sizeof(Options));
    opts->pFlag = 2;
    opts->sFlag = 2;
    opts->UFlag = 2;
    opts->SFlag = 2;
    opts->vFlag = 2;
    opts->cFlag = 2;




  while ((command = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
    expectedArgs++;
    switch (command) {
      case 'p': {
        if (atoi(optarg)) {
          opts->pFlag = atoi(optarg);
          if (opts->pFlag < 0) {
            errMsg = BAD_PID_INPUT_ERROR;
            return NULL;
          }
        }
        else if (*optarg == '0') {
          opts->pFlag = 0;
        }
        else {
          errMsg = BAD_PID_INPUT_ERROR; 
          return NULL;
        }
        expectedArgs++;
        break;
      }
      case 's': {
        printf("made to -s\n");
        if (opts->sFlag == 2) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->sFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
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
          return NULL;
        }
        break;
      }
      case 'U': {
        if (opts->UFlag == 2) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->UFlag = 0;
             }
             else {
               errMsg = USAGE_ERROR;
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
          return NULL;
          //duplicate flag error
        }
        break;
      }
      case 'S': {
        if (opts->SFlag == 2) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->SFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
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
        if (opts->vFlag == 2) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->vFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
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
          return NULL;
          //duplicate flag error
        }
        break;
      }
      case 'c': {
       if (opts->cFlag == 2) {
           if (optarg) {
             if (*optarg == '-') {
               //-s- case
               opts->cFlag = 0;
             }
             else {
               //gibberish arg
               errMsg = USAGE_ERROR;
               return NULL;
             }
           }
           else {
             //-s case
             opts->cFlag = 1;
           }
        }
        else {
          //duplicate flag error
          errMsg = DUPLICATE_FLAG_ERROR;
          return NULL;
        }
        break;
      }
      case '?': {
        printf("case ?\n");
        errMsg = USAGE_ERROR;
        return NULL;
      }
      default: {
        return NULL;
      }
    }
  }

  if (expectedArgs + 1 != argc) {
    printf("invalid arguments\n");
    errMsg = COMMAND_FORMAT_ERROR;
    return NULL;
  }


return opts;

}