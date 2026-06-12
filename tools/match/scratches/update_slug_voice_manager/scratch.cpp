// update_slug_voice_manager @ 0x43f5e0 (thiscall, ret)

class SlugVoiceManager {
public:
    void update_slug_voice_manager();

    unsigned char active; // +0x00
    char pad_01[3];
    float progress;      // +0x04
    float step;          // +0x08
};

void SlugVoiceManager::update_slug_voice_manager()
{
    if (progress > 0.0f) {
        float next_progress = step + progress;
        progress = next_progress;
        if (next_progress > 1.0f) {
            progress = 0.0f;
            active = 0;
        }
    }
}
