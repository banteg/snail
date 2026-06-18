// register_sound_sample @ 0x432f10 (cdecl)

#include "audio_system.h"

extern char* g_music_memory_buffer; // data_53c7e8
extern int g_archive_index_records; // data_53c7f8
extern char g_registered_sound_sample_names[256][0x80]; // data_5088b0
extern int g_registered_sound_sample_count; // data_5108b0

char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, int* out_size);
void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

int register_sound_sample(char* path, int normalization_class)
{
    int archive_index_records = g_archive_index_records;
    char* source_path;
    if (archive_index_records != 0) {
        source_path = path;
        load_file_bytes_from_archive_or_fs(path, g_music_memory_buffer, (int*)&path);
        g_audio_backend.load_registered_sound_sample_from_bytes(
            g_music_memory_buffer,
            (int)path,
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
    if (next_count == 256) {
        g_registered_sound_sample_count = 255;
        report_errorf("Run out of Sound slots increase RSHELL_SOUND_MAX in RShell.h");
        next_count = g_registered_sound_sample_count;
    }

    return next_count - 1;
}
