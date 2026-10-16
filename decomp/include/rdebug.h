#ifndef RDEBUG_H
#define RDEBUG_H

#include "rerror.h"

// The reporter's recovered no-op sink has C++ linkage: under /GX, VC6 treats
// an extern "C" callee as nothrow, which would drop the unwind-state reset that
// construct_game_runtime keeps after its last `new`.
int debug_report_stub(char* format, ...);

#endif
