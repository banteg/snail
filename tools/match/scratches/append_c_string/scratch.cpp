// append_c_string @ 0x431e50 (cdecl)

#include "rtext.h"

void __cdecl append_c_string(char* destination, char* source)
{
    char* result = destination;
    if (*result != '\0') {
        char value;
        do {
            value = result[1];
            ++result;
        } while (value != '\0');
    }

    char* cursor = source;
    char value = *source;
    while (value != '\0') {
        *result = value;
        ++result;
        ++cursor;
        value = *cursor;
    }
    *result = '\0';
}
