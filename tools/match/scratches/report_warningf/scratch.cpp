// report_warningf @ 0x431d10 (cdecl)

#include <stdarg.h>

int vsprintf(char* buffer, char* format, va_list args);
int debug_report_stub(char* format, ...);

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
