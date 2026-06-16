// strings_equal_case_insensitive_path @ 0x44e6c0 (cdecl)

int __cdecl strings_equal_case_insensitive_path(char* left, char* right)
{
    while (1) {
        char left_value = *left;
        char right_value = *right;
        ++left;
        ++right;

        if (left_value >= 'a' && left_value <= 'z')
            left_value -= 0x20;
        if (right_value >= 'a' && right_value <= 'z')
            right_value -= 0x20;

        if (left_value != '\0' && right_value != '\0' && left_value == right_value)
            continue;
        if (left_value == '\0' && right_value == '\0')
            return 1;
        return 0;
    }
}
