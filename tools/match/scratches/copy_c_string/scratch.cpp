// copy_c_string @ 0x431da0 (cdecl)

#include "rtext.h"

void __cdecl copy_c_string(char* destination, char* source)
{
    do {
        *destination++ = *source;
    } while (*source++ != '\0');
}
