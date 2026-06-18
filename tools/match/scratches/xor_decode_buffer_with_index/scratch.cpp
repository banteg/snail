// xor_decode_buffer_with_index @ 0x433010 (cdecl)

char* xor_decode_buffer_with_index(char* bytes, int byte_count)
{
    char* result = bytes;
    int index = 0;
    if (byte_count > 0) {
        do {
            *result ^= (char)index;
            ++result;
            ++index;
        } while (index < byte_count);
    }
    return result;
}
