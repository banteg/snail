// register_sound_sample @ 0x432f10 (cdecl)

#include "audio_system.h"
#include "archive_index.h"

extern char* g_music_memory_buffer; // data_53c7e8

char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, int* out_size);
void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

int register_sound_sample(char* path, int normalization_class)
{
    ArchiveIndex* archive_index_records = g_archive_index_records;
    char* source_path;
    int sample_size;
    if (archive_index_records != 0) {
        source_path = path;
        load_file_bytes_from_archive_or_fs(path, g_music_memory_buffer, &sample_size);
        g_audio_backend.load_registered_sound_sample_from_bytes(
            g_music_memory_buffer,
            sample_size,
            g_registered_sound_sample_count,
            normalization_class);
    } else {
        source_path = path;
        g_audio_backend.load_registered_sound_sample_from_path(
            path, g_registered_sound_sample_count, normalization_class);
    }

    rstrcpy_checked_ascii(
        g_registered_sound_sample_names[g_registered_sound_sample_count],
        source_path);

    int next_count = g_registered_sound_sample_count + 1;
    g_registered_sound_sample_count = next_count;
    if (next_count == RSHELL_SOUND_MAX) {
        g_registered_sound_sample_count = RSHELL_SOUND_MAX - 1;
        report_errorf("Run out of Sound slots increase RSHELL_SOUND_MAX in RShell.h");
        next_count = g_registered_sound_sample_count;
    }

    return next_count - 1;
}
