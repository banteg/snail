// append_c_string @ 0x431e50 (cdecl)

unsigned char* __cdecl append_c_string(unsigned char* destination, unsigned char* source)
{
    unsigned char* result = destination;
    if (*result != '\0') {
        unsigned char value;
        do {
            value = result[1];
            ++result;
        } while (value != '\0');
    }

    unsigned char* cursor = source;
    unsigned char value = *source;
    while (value != '\0') {
        *result = value;
        ++result;
        ++cursor;
        value = *cursor;
    }
    *result = '\0';
    return result;
}
