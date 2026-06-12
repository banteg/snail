// skip_to_next_line @ 0x431e30 (cdecl)

unsigned char* __cdecl skip_to_next_line(unsigned char** cursor)
{
    unsigned char* result = *cursor;
    while (*result != '\0') {
        result = *cursor;
        if (*result == '\n') {
            break;
        }
        result = result + 1;
        *cursor = result;
    }
    *cursor = *cursor + 1;
    return result;
}
