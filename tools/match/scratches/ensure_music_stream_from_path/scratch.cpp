// ensure_music_stream_from_path @ 0x449720 (thiscall, ret 0x8)

#include "audio_system.h"
#include <string.h>

typedef int (__stdcall* BassStreamCreateFileFn)(
    int from_memory, char* path_or_bytes, int offset, int byte_count, int flags);
typedef int (__stdcall* BassChannelPlayFn)(int stream, int restart, int flags);

extern int g_active_music_stream; // 0x753c20
extern BassChannelPlayFn g_bass_channel_play; // 0x7517a0
extern BassStreamCreateFileFn g_bass_stream_create_file; // 0x753bf8

int strings_equal_case_insensitive_path(char* left, char* right); // @ 0x44e6c0
void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

int AudioBackend::ensure_music_stream_from_path(char* path, char play_mode)
{
    register AudioBackend* backend = this;
    if (music_stream_active) {
        int same_path = strings_equal_case_insensitive_path(path, g_cached_music_path);
        if (same_path != 0) {
            return same_path;
        }
        backend->stop_music_stream();
    }

    register char* source_path = path;
    register int path_length = strlen(source_path);
    rstrcpy_checked_ascii(g_cached_music_path, source_path);

    if (g_active_music_stream != 0) {
        backend->stop_music_stream();
    }
    g_active_music_stream = 0;

    if (path_length > 4) {
        int stream = g_bass_stream_create_file(0, source_path, 0, 0, 0);
        g_active_music_stream = stream;
        if (stream != 0) {
            int result;
            if (play_mode) {
                result = g_bass_channel_play(stream, 0, 4);
            } else {
                result = g_bass_channel_play(stream, 0, 0);
            }
            backend->music_stream_active = 1;
            return result;
        }
    }
    return report_errorf("Music Play Memory Failed %s", source_path);
}
