// file_exists @ 0x405140 (cdecl)

struct File;

extern "C" File* __cdecl fopen(char* path, char* mode);
extern "C" int __cdecl fclose(File* file);

char __cdecl file_exists(char* path)
{
    File* file = fopen(path, "rb");
    if (file == 0) {
        return 0;
    }
    fclose(file);
    return 1;
}
