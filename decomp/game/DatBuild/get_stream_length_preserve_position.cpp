// get_stream_length_preserve_position @ 0x405170 (cdecl)

#include <stdio.h>

int __cdecl get_stream_length_preserve_position(FILE* file)
{
    long position = ftell(file);
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, position, SEEK_SET);
    return length;
}
