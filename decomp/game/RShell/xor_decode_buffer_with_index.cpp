// xor_decode_buffer_with_index @ 0x433010 (cdecl)
// Authored mobile name: RShellScrambleFile(void*, int)

void xor_decode_buffer_with_index(void* buffer, int byte_count)
{
    char* result = (char*)buffer;
    int index = 0;
    if (byte_count > 0) {
        do {
            *result ^= (char)index;
            ++result;
            ++index;
        } while (index < byte_count);
    }
}
