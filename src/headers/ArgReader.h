char* errMsg;

typedef struct Options {
  int pFlag;
  int sFlag;
  int UFlag;
  int SFlag;
  int vFlag;
  int cFlag;
} Options;


int getOpts(Options *opts, int argc, char **argv);
