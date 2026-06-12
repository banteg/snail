// parse_next_space_delimited_token @ 0x431e80 (cdecl)

char** __cdecl parse_next_space_delimited_token(char** cursor, char* out)
{
    char** result = cursor;

    if (**cursor == ' ') {
        char* next;
        do {
            next = *cursor + 1;
            *cursor = next;
        } while (*next == ' ');
    }

    char* current_ptr = *cursor;
    char current = *current_ptr;
    char* out_cursor = out;
    if (current != ' ') {
        while (current != ' ') {
            current_ptr = *cursor;
            char value = *current_ptr;
            if (value == '\r') {
                break;
            }
            *out_cursor = value;
            ++out_cursor;
            current_ptr = *cursor + 1;
            *cursor = current_ptr;
            current = *current_ptr;
        }
    }

    *out_cursor = '\0';
    return result;
}
