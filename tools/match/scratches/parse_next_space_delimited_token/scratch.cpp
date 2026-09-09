// RTextExtractString @ 0x431e80 (cdecl)

#include "rtext.h"

void __cdecl RTextExtractString(char** cursor, char* out)
{
    while (**cursor == ' ') {
        ++*cursor;
    }

    while (**cursor != ' ') {
        if (**cursor == '\r') {
            break;
        }
        *out++ = **cursor;
        ++*cursor;
    }

    *out = '\0';
}
