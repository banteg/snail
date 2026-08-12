// RTextCopy @ 0x431da0 (cdecl)

#include "rtext.h"

void __cdecl RTextCopy(char* destination, char* source)
{
    do {
        *destination++ = *source;
    } while (*source++ != '\0');
}
