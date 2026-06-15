// get_stream_length_preserve_position @ 0x405170 (cdecl)

struct File;

extern "C" int __cdecl ftell(File* file);
extern "C" int __cdecl fseek(File* file, int offset, int origin);

int __cdecl get_stream_length_preserve_position(File* file)
{
    int position = ftell(file);
    fseek(file, 0, 2);
    int length = ftell(file);
    fseek(file, position, 0);
    return length;
}
