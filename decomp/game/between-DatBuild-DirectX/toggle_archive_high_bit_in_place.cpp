// toggle_archive_high_bit_in_place @ 0x405350 (cdecl)

char* toggle_archive_high_bit_in_place(char* data, int count)
{
    char* result = data;

    if (count > 0) {
        do {
            *result ^= 0x80;
            ++result;
            --count;
        } while (count != 0);
    }

    return result;
}
