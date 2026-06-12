// play_slug_voice @ 0x43f560 (thiscall, ret 0x4)

extern char* g_game_base; // data_4df904
void play_voice_backend(int sample_id, float volume, float pan, float frequency);

class SlugHazardRuntime {
public:
    void play_slug_voice(int sample_index);

    char unknown_00[0xd8];
    unsigned char voice_active; // +0xd8
    char unknown_d9[3];
    float voice_progress;      // +0xdc
    float voice_progress_step; // +0xe0
};

void SlugHazardRuntime::play_slug_voice(int sample_index)
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
