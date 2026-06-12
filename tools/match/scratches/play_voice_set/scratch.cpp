// play_voice_set @ 0x449390 (thiscall, ret 0x4)

void play_voice_backend(int sample_id, float volume, float pan, float frequency);

class VoiceSet {
public:
    bool play_voice_set(int sample_override);

    int sample_count;          // +0x00
    int next_index;            // +0x04
    int* playlist;             // +0x08
    int* bites;                // +0x0c
    float cooldown;            // +0x10
    float cooldown_step;       // +0x14
};

bool VoiceSet::play_voice_set(int sample_override)
{
    while (cooldown == 0.0f) {
        cooldown = cooldown_step;
        if (sample_override == -1) {
            int sample_index = playlist[next_index];
            play_voice_backend(bites[sample_index], 1.0f, -1.0f, 0.0f);
            int next = next_index;
            int count = sample_count;
            ++next;
            next_index = next;
            if (next_index == count) {
                next_index = 0;
                return true;
            }
            return true;
        }

        play_voice_backend(sample_override, 1.0f, -1.0f, 0.0f);
        return true;
    }
    return false;
}
