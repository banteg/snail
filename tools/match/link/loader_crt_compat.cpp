// Diagnostic ABI bridges for historical C++ declarations of CRT sprintf.
#include <stdarg.h>
extern "C" int __cdecl vsprintf(char*, const char*, va_list);
extern "C" void loader_error(char*, va_list);
void report_errorf(char* format, ...)
{ va_list args; va_start(args, format); loader_error(format, args); va_end(args); }
int sprintf(char* out, char* format, ...)
{ va_list args; va_start(args, format); int n = vsprintf(out, format, args); va_end(args); return n; }
int sprintf(char* out, const char* format, ...)
{ va_list args; va_start(args, format); int n = vsprintf(out, format, args); va_end(args); return n; }
