// find_case_insensitive_substring @ 0x44e600 (cdecl)

char ascii_upper_if_lowercase(char value); // @ 0x44e5a0

char* __cdecl find_case_insensitive_substring(char* haystack, char* needle)
{
    char* result = needle;
    if (*result == 0)
        return 0;

    do {
        char haystack_first = *haystack;
        char* needle_cursor = needle;
        char needle_first = *needle_cursor;
        char upper_haystack = ascii_upper_if_lowercase(haystack_first);
        char upper_needle = ascii_upper_if_lowercase(needle_first);
        if (upper_needle == upper_haystack) {
            int delta = haystack - needle_cursor;
            do {
                char next_haystack = *(delta + needle_cursor + 1);
                ++needle_cursor;
                if (next_haystack == 0) {
                    if (*needle_cursor == 0)
                        return haystack;
                    break;
                }
                if (*needle_cursor == 0)
                    return 0;
                char upper_left = ascii_upper_if_lowercase(*needle_cursor);
                char upper_right = ascii_upper_if_lowercase(*(delta + needle_cursor));
                if (upper_left != upper_right)
                    break;
            } while (1);
        }

        if (*needle == 0)
            return haystack;
        ++haystack;
        result = haystack;
    } while (*result != 0);

    return 0;
}
