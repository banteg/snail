// scramble_archive_bytes_in_place @ 0x405270 (cdecl)

void scramble_archive_bytes_in_place(char* bytes, int size)
{
    for (int i = 0; i < size; ++i) {
        char index = (char)i;
        bytes[i] ^= (char)((index * index) ^ (index * 3));
    }
}
