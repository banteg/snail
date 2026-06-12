// update_voice_set @ 0x449360 (thiscall, ret)

class VoiceSet {
public:
    void update_voice_set();

    char unknown_00[0x10];
    float progress;            // +0x10
    float progress_step;       // +0x14
};

void VoiceSet::update_voice_set()
{
    if (progress > 0.0f) {
        float next_progress = progress_step + progress;
        progress = next_progress;
        if (next_progress > 1.0f) {
            progress = 0.0f;
        }
    }
}
