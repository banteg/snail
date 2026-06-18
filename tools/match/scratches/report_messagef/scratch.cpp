// report_messagef @ 0x431d60 (cdecl)

#include <stdarg.h>

int vsprintf(char* buffer, char* format, va_list args);
int debug_report_stub(char* format, ...);

int report_messagef(char* format, ...)
{
    char buffer[4096];
    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    return debug_report_stub("%s", buffer);
}
