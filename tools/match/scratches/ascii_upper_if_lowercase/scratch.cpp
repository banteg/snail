// RstrASC @ 0x44e5a0 (cdecl, ret char)

#include "rstring.h"

char __cdecl RstrASC(char value)
{
    if (value >= 'a' && value <= 'z')
        return value - 0x20;
    return value;
}
