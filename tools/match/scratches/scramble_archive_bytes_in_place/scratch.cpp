// scramble_archive_bytes_in_place @ 0x405270 (cdecl)
// Authored mobile name: RShellScrambleFileDat(void*, int)

void scramble_archive_bytes_in_place(void* buffer, int size)
{
    char* bytes = (char*)buffer;
    for (int i = 0; i < size; ++i) {
        char index = (char)i;
        bytes[i] ^= (char)((index * index) ^ (index * 3));
    }
}
