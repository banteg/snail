typedef int int32_t;

int32_t __cdecl parse_next_int32(char** cursor);
char** __cdecl parse_next_space_delimited_token(char** cursor, char* out);
double __cdecl parse_next_float32(char** cursor);
