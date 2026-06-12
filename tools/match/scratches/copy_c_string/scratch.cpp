// copy_c_string @ 0x431da0 (cdecl)

unsigned char* __cdecl copy_c_string(unsigned char* destination, unsigned char* source)
{
    unsigned char* cursor = source;
    unsigned char value;
    do {
        *destination = *cursor;
        value = *cursor;
        ++destination;
        ++cursor;
    } while (value != '\0');
    return cursor;
}
