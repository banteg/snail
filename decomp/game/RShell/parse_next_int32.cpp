// RTextExtractInt @ 0x431ec0 (cdecl)

#include "rtext.h"

int __cdecl RTextExtractInt(char** cursor)
{
    if (**cursor == ' ') {
        do {
            *cursor = *cursor + 1;
        } while (**cursor == ' ');
    }

    int sign;
    if (**cursor == '-') {
        sign = -1;
        *cursor = *cursor + 1;
    } else {
        sign = 1;
    }

    int value = 0;
    while (**cursor >= '0') {
        char* current = *cursor;
        char digit = **cursor;
        if (digit > '9') {
            break;
        }
        value = digit + value * 10 - '0';
        *cursor = current + 1;
    }

    return sign * value;
}
