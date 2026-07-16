// play_music_stream_from_bytes @ 0x449820 (thiscall, ret 0x10)

#include "audio_system.h"
#include <string.h>

void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

int AudioBackend::play_music_stream_from_bytes(
    char* path, char* bytes, int byte_count, char play_mode)
{
    register AudioBackend* backend = this;
    register char* source_path = path;
    register int path_length = strlen(source_path);
    rstrcpy_checked_ascii(g_cached_music_path, source_path);

    if (g_active_music_stream != 0) {
        backend->stop_music_stream();
    }
    g_active_music_stream = 0;

    if (path_length > 4) {
        int stream = g_bass_stream_create_file(1, bytes, 0, byte_count, 0);
        g_active_music_stream = stream;
        if (stream != 0) {
            int result;
            if (play_mode) {
                result = g_bass_stream_play(stream, 0, 4);
            } else {
                result = g_bass_stream_play(stream, 0, 0);
            }
            backend->music_stream_active = 1;
            return result;
        }
    }
    return report_errorf("Music Play Memory Failed %s", source_path);
}
