// update_slug_voice_ai @ 0x43f520 (thiscall, ret)

class SlugHazardRuntime {
public:
    void update_slug_voice_ai();

    char unknown_00[0xd8];
    unsigned char voice_active; // +0xd8
    char unknown_d9[3];
    float voice_progress;      // +0xdc
    float voice_progress_step; // +0xe0
};

void SlugHazardRuntime::update_slug_voice_ai()
{
    if (voice_active != 0) {
        float next_progress = voice_progress_step + voice_progress;
        voice_progress = next_progress;
        if (next_progress > 1.0f) {
            voice_progress = 0.0f;
            voice_active = 0;
        }
    }
}
