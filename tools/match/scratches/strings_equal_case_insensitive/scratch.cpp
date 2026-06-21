// strings_equal_case_insensitive @ 0x431dc0 (cdecl)

bool __cdecl strings_equal_case_insensitive(char* left, char* right)
{
    char right_upper = *right;
    char left_upper = *left;
    char right_value = right_upper;
    char left_value = left_upper;

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
        ++right;
        right_upper = *right;
        left_upper = *left;
        right_value = right_upper;
        left_value = left_upper;

        if (left_upper >= 'a' && left_upper <= 'z')
            left_upper -= 0x20;
        if (right_upper >= 'a' && right_upper <= 'z')
            right_upper -= 0x20;
    }

    if (*right == 0)
        return true;
    return false;
}
