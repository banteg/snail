// classify_archive_entry_extension @ 0x4050c0 (cdecl)

enum ArchiveEntryExtensionClass {
    ARCHIVE_ENTRY_EXTENSION_UNKNOWN = 0,
    ARCHIVE_ENTRY_EXTENSION_TGA = 1,
    ARCHIVE_ENTRY_EXTENSION_WAV = 2,
    ARCHIVE_ENTRY_EXTENSION_MP3 = 3,
};

int __cdecl classify_archive_entry_extension(unsigned char* path, unsigned char* stem_out)
{
    unsigned char* output = stem_out;
    unsigned char value = *path;
    while (value != 0) {
        if (value == '.')
            break;
        ++path;
        *output = value;
        ++output;
        value = *path;
    }

    *output = 0;
    value = *path;
    if (value == 0)
        return ARCHIVE_ENTRY_EXTENSION_UNKNOWN;

    value = *++path;
    char letter_a = 'A';
    if (value == 'T' && path[1] == 'G' && path[2] == letter_a)
        return ARCHIVE_ENTRY_EXTENSION_TGA;
    else if (value == 'W' && path[1] == letter_a && path[2] == 'V')
        return ARCHIVE_ENTRY_EXTENSION_WAV;
    else if (value == 'M' && path[1] == 'P' && path[2] == '3')
        return ARCHIVE_ENTRY_EXTENSION_MP3;
    return ARCHIVE_ENTRY_EXTENSION_UNKNOWN;
}
