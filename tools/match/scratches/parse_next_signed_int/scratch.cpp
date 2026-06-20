// parse_next_signed_int @ 0x44e710 (cdecl)

int __cdecl parse_next_signed_int(char** cursor)
{
    char* current = *cursor;
    if (*current != '-') {
        do {
            current = *cursor;
            char value = *current;
            if (value == '+')
                break;
            if (value == '.')
                break;
            if (value >= '0' && value <= '9')
                break;
            *cursor = current + 1;
        } while (current[1] != '-');
    }

    current = *cursor;
    int sign;
    if (*current == '-') {
        sign = -1;
        ++current;
        *cursor = current;
    } else {
        sign = 1;
    }

    int value = 0;
    current = *cursor;
    while (*current >= '0') {
        char digit = *current;
        if (digit > '9')
            break;
        value = digit + value * 10 - '0';
        ++current;
        *cursor = current;
    }

    return value * sign;
}
