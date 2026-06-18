// xor_archive_bytes_in_place @ 0x431980 (cdecl)

void __cdecl xor_archive_bytes_in_place(int start_offset, char* bytes, int count)
{
    int index = start_offset;
    int end_offset = start_offset + count;
    if (index < end_offset) {
        char* rebased = bytes - start_offset;
        do {
            char low_index = (char)index;
            rebased[index] ^= (char)((low_index * low_index) ^ (low_index * 3));
            ++index;
        } while (index < end_offset);
    }
}
