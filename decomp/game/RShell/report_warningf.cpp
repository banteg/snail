// report_warningf @ 0x431d10 (cdecl)

#include <stdarg.h>
#include <stdio.h>

#include "rdebug.h"

int report_warningf(char* format, ...)
{
    char buffer[4096];
    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    debug_report_stub("* WARNING * ");
    debug_report_stub("%s", buffer);
    return debug_report_stub("\n");
}
