#ifndef _ARGREADER
#define _ARGREADER

extern char* errMsg;

typedef struct Options {
  int pFlag;
  int sFlag;
  int UFlag;
  int SFlag;
  int vFlag;
  int cFlag;
} Options;


extern Options * getOpts(int argc, char **argv);
#endif