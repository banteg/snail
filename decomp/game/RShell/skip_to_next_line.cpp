// RTextNewLine @ 0x431e30 (cdecl)

#include "rtext.h"

void __cdecl RTextNewLine(char** cursor)
{
    char* result = *cursor;
    while (*result != '\0') {
        result = *cursor;
        if (*result == '\n') {
            break;
        }
        result = result + 1;
        *cursor = result;
    }
    *cursor = *cursor + 1;
}
