/**
 ============================================================================
 Name        : exampleProgram.c
 Author      : Joao Pereira
 Version     :
 Copyright   : This library is creating under the ASF License version 2.0
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libJPReactor/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */
#include <unistd.h>
#include <iostream>

#define MAX_PROCESS 5
using namespace jpCppLibs;

int main(void) {

  OneInstanceLogger::instance()->log("Ended APP","SEM",M_LOG_NRM,M_LOG_DBG);
  return 0;
}
