// Voice playback manager views, partial.
#ifndef VOICE_MANAGER_H
#define VOICE_MANAGER_H

class VoiceSet {
public:
    int initialize_voice_set(int count); // @ 0x448df0
    int shuffle_voice_set(); // @ 0x448e60
    bool play_voice_set(int sample_override); // @ 0x449390
    void update_voice_set(); // @ 0x449360

    int sample_count;          // +0x00
    int next_index;            // +0x04
    int* playlist;             // +0x08
    int* bites;                // +0x0c
    float cooldown;            // +0x10
    float cooldown_step;       // +0x14
};

class VoiceManager {
public:
    void reset_voice_manager(); // @ 0x448ec0
    void update_voice_manager(); // @ 0x4492a0
    bool play_voice_manager(int set_id, unsigned int mode, int sample_override); // @ 0x4492d0
    int is_voice_playing(); // @ 0x449410

    VoiceSet sets[16];              // +0x000
    float global_progress;           // +0x180
    float global_frequency_seconds;  // +0x184
};

extern VoiceManager g_voice_manager; // unk_751498

typedef char VoiceSet_must_be_0x18[(sizeof(VoiceSet) == 0x18) ? 1 : -1];
typedef char VoiceManager_must_be_0x188[
    (sizeof(VoiceManager) == 0x188) ? 1 : -1];

#endif
