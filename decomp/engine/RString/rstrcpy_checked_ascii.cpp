// Rstrcpy @ 0x44e5b0 (cdecl)

#include "rstring.h"

void report_errorf(char* format, ...);

void __cdecl Rstrcpy(char* destination, const char* source)
{
    const char* source_cursor = source;
    char value = *source_cursor;
    if (value != 0) {
        char* destination_cursor = destination;
        do {
            *destination_cursor = value;
            value = *source_cursor;
            if ((int)value > 0x80 || value < 0) {
                report_errorf("Dodgy Rstrcpy %s", source_cursor);
            }
            value = source_cursor[1];
            ++destination_cursor;
            ++source_cursor;
        } while (value != 0);
        *destination_cursor = value;
        return;
    }

    *destination = 0;
}
