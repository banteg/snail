#ifndef RDEBUG_H
#define RDEBUG_H

#include "rerror.h"

// The reporter's recovered no-op sink also has a shared C ABI.
#ifdef __cplusplus
extern "C" {
#endif
int debug_report_stub(char* format, ...);
#ifdef __cplusplus
}
#endif

#endif
