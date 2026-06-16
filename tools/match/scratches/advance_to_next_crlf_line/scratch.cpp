// advance_to_next_crlf_line @ 0x44e690 (cdecl)

char* __cdecl advance_to_next_crlf_line(char* cursor)
{
    while (*cursor != '\0') {
        if (*cursor == '\r' && cursor[1] == '\n')
            return cursor[2] != '\0' ? cursor + 2 : 0;
        ++cursor;
    }

    return 0;
}
