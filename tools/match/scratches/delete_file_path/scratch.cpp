// delete_file_path @ 0x405340 (cdecl)

extern "C" int __cdecl remove(char* path);

void __cdecl delete_file_path(char* path)
{
    remove(path);
}
