// find_case_insensitive_substring @ 0x44e600 (cdecl)

#include "rstring.h"

char* __cdecl find_case_insensitive_substring(char* needle, char* haystack)
{
    char* haystack_cursor = haystack;
    if (*haystack_cursor != 0) {
        while (1) {
            char* needle_cursor = needle;
            char haystack_upper = ascii_upper_if_lowercase(*haystack_cursor);
            if (ascii_upper_if_lowercase(*needle) == haystack_upper) {
                int delta = haystack_cursor - needle;
                while (1) {
                    ++needle_cursor;
                    if (needle_cursor[delta] == 0 && *needle_cursor != 0)
                        return 0;
                    if (needle_cursor[delta] == 0 && *needle_cursor == 0)
                        goto found;

                    char needle_upper =
                        ascii_upper_if_lowercase(*needle_cursor);
                    if (needle_upper == ascii_upper_if_lowercase(needle_cursor[delta]))
                        continue;
                    goto advance_haystack;
                }
            }

advance_haystack:
            if (*needle_cursor != 0) {
                ++haystack_cursor;
                if (*haystack_cursor == 0)
                    return 0;
                continue;
            }
            goto found;
        }
    }
    return 0;

found:
    return haystack_cursor;
}
