// RTextCompStart @ 0x431dc0 (cdecl)

#include "rtext.h"

bool __cdecl RTextCompStart(char* left, char* prefix)
{
    char right_value = *prefix;
    char left_value = *left;
    char right_upper = *prefix;
    char left_upper = *left;

    if (left_upper >= 'a' && left_upper <= 'z')
        left_upper -= 0x20;
    if (right_upper >= 'a' && right_upper <= 'z')
        right_upper -= 0x20;

    while (left_value != 0) {
        if (right_value == 0)
            break;
        if (left_upper != right_upper)
            break;

        ++left;
        ++prefix;
        right_value = *prefix;
        left_value = *left;
        right_upper = *prefix;
        left_upper = *left;

        if (left_upper >= 'a' && left_upper <= 'z')
            left_upper -= 0x20;
        if (right_upper >= 'a' && right_upper <= 'z')
            right_upper -= 0x20;
    }

    if (*prefix == 0)
        return true;
    return false;
}
