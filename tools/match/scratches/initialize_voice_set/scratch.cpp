// initialize_voice_set @ 0x448df0 (thiscall, ret 0x4)

void* allocate_tracked_memory(int size, char* label);

class VoiceSet {
public:
    int initialize_voice_set(int count);
    int shuffle_voice_set();

    int sample_count;          // +0x00
    int next_index;            // +0x04
    int* playlist;             // +0x08
    int* bites;                // +0x0c
    float cooldown;            // +0x10
    float cooldown_step;       // +0x14
};

int VoiceSet::initialize_voice_set(int count)
{
    sample_count = count;
    next_index = 0;
    playlist = (int*)allocate_tracked_memory(count << 2, "Playlist");
    bites = (int*)allocate_tracked_memory(sample_count << 2, "VoiceBite");
    int current_count = sample_count;
    cooldown = 0.0f;
    cooldown_step = 0.0041666669f;
    int index = 0;
    if (current_count > 0) {
        do {
            playlist[index] = index;
            ++index;
        } while (index < sample_count);
    }
    return shuffle_voice_set();
}
