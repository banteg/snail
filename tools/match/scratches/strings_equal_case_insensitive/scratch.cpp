// strings_equal_case_insensitive @ 0x431dc0 (cdecl)

unsigned char __cdecl strings_equal_case_insensitive(char* left, char* right)
{
    char* left_cursor = left;
    char* right_cursor = right;
    char right_char = *right_cursor;
    char left_char = *left_cursor;
    char right_upper = right_char;
    char left_upper = left_char;

    if (left_upper >= 'a' && left_upper <= 'z')
        left_upper -= 0x20;
    if (right_upper >= 'a' && right_upper <= 'z')
        right_upper -= 0x20;

    while (left_char != 0 && right_char != 0) {
        if (left_upper != right_upper)
            break;
        ++left_cursor;
        ++right_cursor;
        left_char = *left_cursor;
        right_char = *right_cursor;
        left_upper = left_char;
        right_upper = right_char;
        if (left_upper >= 'a' && left_upper <= 'z')
            left_upper -= 0x20;
        if (right_upper >= 'a' && right_upper <= 'z')
            right_upper -= 0x20;
    }

    return *right_cursor == 0;
}
