// cache_music_file @ 0x432d50 (cdecl)

#include "audio_system.h"
#include "archive_index.h"

char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, int* out_size);
int report_errorf(char* format, ...);

char cache_music_file(char* path, int unused, char* unused_default_path)
{
    char result;
    if (g_archive_index_records != 0) {
        char* source_path = path;
        result = g_audio_backend.prepare_music_stream_reload_if_path_changed(path);
        if (result != 0) {
            char* bytes =
                load_file_bytes_from_archive_or_fs(source_path, g_music_memory_buffer, (int*)&path);
            if ((int)path >= RSHELL_MUSIC_MEMORY_BUFFER_SIZE) {
                report_errorf("Music buffer overflow Increase RSHELL_MUSIC_MEMORY_BUFFER_SIZE");
            }

            return g_audio_backend.play_music_stream_from_bytes(source_path, bytes, (int)path, 1);
        }
    } else {
        result = g_audio_backend.ensure_music_stream_from_path(path, 1);
    }

    return result;
}
