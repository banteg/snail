// copy_c_string @ 0x431da0 (cdecl)

unsigned char* __cdecl copy_c_string(unsigned char* destination, unsigned char* source)
{
    do {
        *destination++ = *source;
    } while (*source++ != '\0');
    return source;
}
