typedef int int32_t;

/*
 * Native MSVC CRT ABI. The previous two-parameter analysis prototype hid
 * every formatting argument at tracked callsites.
 */
int32_t __cdecl sprintf(char* buffer, const char* format, ...);
