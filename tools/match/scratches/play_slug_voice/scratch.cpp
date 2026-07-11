// play_slug_voice @ 0x43f560 (thiscall, ret 0x4)

#include "slug_hazard_types.h"

extern char* g_game_base; // data_4df904
void play_voice_backend(int sample_id, float volume, float pitch, float pan);

void Slug::play_slug_voice(int sample_index)
{
    if (voice_active == 0) {
        char* game = g_game_base;
        if (*(unsigned char*)(game + 0x3d0194) == 0) {
            *(int*)(game + 0x3d0198) = *(int*)(game + 0x3d019c);
            *(unsigned char*)(g_game_base + 0x3d0194) = 1;
            voice_active = 1;
            voice_progress = 0.0f;
            play_voice_backend(sample_index, 1.0f, -1.0f, 0.0f);
        }
    }
}
