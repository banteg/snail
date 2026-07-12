// classify_archive_entry_extension @ 0x4050c0 (cdecl)

#include "archive_index.h"

ArchiveEntryExtensionClass __cdecl classify_archive_entry_extension(
    unsigned char* path, unsigned char* stem_out)
{
    unsigned char value;
    value = *path;
    unsigned char* output = stem_out;
    while (1) {
        if (value == 0)
            break;
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

    ++path;
    char letter_a = 'A';
    if (*path == 'T' && path[1] == 'G' && path[2] == letter_a)
        return ARCHIVE_ENTRY_EXTENSION_TGA;
    else if (*path == 'W' && path[1] == letter_a && path[2] == 'V')
        return ARCHIVE_ENTRY_EXTENSION_WAV;
    else if (*path == 'M' && path[1] == 'P' && path[2] == '3')
        return ARCHIVE_ENTRY_EXTENSION_MP3;
    return ARCHIVE_ENTRY_EXTENSION_UNKNOWN;
}
