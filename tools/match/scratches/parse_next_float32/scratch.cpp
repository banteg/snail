// parse_next_float32 @ 0x431f20 (cdecl)

float __cdecl parse_next_float32(char** cursor)
{
    while (**cursor != '-') {
        char* current = *cursor;
        char value = *current;
        if (value == '+')
            break;
        if (value == '.')
            break;
        if (value >= '0' && value <= '9')
            break;
        *cursor = current + 1;
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
    while ((**cursor >= '0' && **cursor <= '9') || **cursor == '.') {
        char* current = *cursor;
        char digit = **cursor;
        if (digit == '.') {
            decimal_scale = 1.0f;
            *cursor = current + 1;
        } else {
            int digit_value = digit - '0';
            value = (float)digit_value + value * 10.0f;
            *cursor = current + 1;
            decimal_scale *= 0.1f;
        }
    }

    if (decimal_scale == 0.0f)
        decimal_scale = 1.0f;

    return sign * (decimal_scale * value);
}
