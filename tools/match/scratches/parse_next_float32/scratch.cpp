// parse_next_float32 @ 0x431f20 (cdecl)

float __cdecl parse_next_float32(char** cursor)
{
    if (**cursor != '-') {
        char* current;
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

    float sign;
    if (**cursor == '-') {
        sign = -1.0f;
        *cursor = *cursor + 1;
    } else {
        sign = 1.0f;
    }

    float value = 0.0f;
    float decimal_scale = 0.0f;
    while (1) {
        char* current = *cursor;
        char digit = *current;
        if ((digit < '0' || digit > '9') && digit != '.')
            break;
        if (digit == '.') {
            decimal_scale = 1.0f;
            *cursor = current + 1;
        } else {
            *cursor = current + 1;
            value = (float)(digit - '0') + value * 10.0f;
            decimal_scale *= 0.1f;
        }
    }

    if (decimal_scale == 0.0f)
        decimal_scale = 1.0f;

    return sign * (decimal_scale * value);
}
