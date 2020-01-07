#include "parser.h"
#include "executor.h"

#ifndef _rshell_h
#define _rshell_h

class rShell{
  public:
    void run();

  private:
    parser shellparse;
    executor shellexec;
};

#endif
