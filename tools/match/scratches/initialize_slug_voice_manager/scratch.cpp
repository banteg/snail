// initialize_slug_voice_manager @ 0x43f5c0 (thiscall, ret)

class SlugVoiceManager {
public:
    void initialize_slug_voice_manager();

    unsigned char active; // +0x00
    char pad_01[3];
    float progress;      // +0x04
    float step;          // +0x08
};

void SlugVoiceManager::initialize_slug_voice_manager()
{
    active = 0;
    progress = 0.0f;
    step = 0.016666668f;
}
