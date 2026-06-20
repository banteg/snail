// parse_next_signed_int @ 0x44e710 (cdecl)

int __cdecl parse_next_signed_int(char** cursor)
{
    while (**cursor != '-') {
        char* current;
        current = *cursor;
        char value = *current;
        if (value == '+')
            break;
        if (value == '.')
            break;
        if (value >= '0' && value <= '9')
            break;
        *cursor = current + 1;
    }

    int sign;
    if (**cursor == '-') {
        sign = -1;
        *cursor = *cursor + 1;
    } else {
        sign = 1;
    }

    int value = 0;
    while (**cursor >= '0') {
        char* current = *cursor;
        char digit = *current;
        if (digit > '9')
            break;
        value = digit + value * 10 - '0';
        ++current;
        *cursor = current;
    }

    return value * sign;
}
