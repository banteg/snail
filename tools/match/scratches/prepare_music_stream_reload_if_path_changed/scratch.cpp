// prepare_music_stream_reload_if_path_changed @ 0x4497e0 (thiscall, ret 0x4)

#include "audio_system.h"

extern char g_cached_music_path[]; // 0x7516a0

int strings_equal_case_insensitive_path(char* left, char* right); // @ 0x44e6c0

char AudioBackend::prepare_music_stream_reload_if_path_changed(char* path)
{
    if (music_stream_active) {
        if (strings_equal_case_insensitive_path(path, g_cached_music_path) != 0) {
            return 0;
        }
        stop_music_stream();
    }

    return 1;
}
