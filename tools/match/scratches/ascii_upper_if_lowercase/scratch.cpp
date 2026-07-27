// ascii_upper_if_lowercase @ 0x44e5a0 (cdecl, ret char)

#include "rstring.h"

char __cdecl ascii_upper_if_lowercase(char value)
{
    if (value >= 'a' && value <= 'z')
        return value - 0x20;
    return value;
}
