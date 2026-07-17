// Windows layouts for the authored cRVoiceSet/cRVoiceManager owners (Voice.o).
#ifndef VOICE_MANAGER_H
#define VOICE_MANAGER_H

// Authored Voice/_Voice.txt bucket order, independently retained by the iOS
// cRVoiceManager::Init jump table and the Windows 16-case initializer.
enum VoiceSetId {
    VOICE_SET_DAMAGE = 0,
    VOICE_SET_DYING = 1,
    VOICE_SET_ENEMIES = 2,
    VOICE_SET_FALL = 3,
    VOICE_SET_MISC = 4,
    VOICE_SET_POWER_UP = 5,
    VOICE_SET_SLOW = 6,
    VOICE_SET_START = 7,
    VOICE_SET_VICTORY = 8,
    VOICE_SET_OUCH = 9,
    VOICE_SET_PACKAGE = 10,
    VOICE_SET_SLUGGED = 11,
    VOICE_SET_WORM_TUNNEL = 12,
    VOICE_SET_TUTORIAL = 13,
    VOICE_SET_POSTAL = 14,
    VOICE_SET_SUPERTRAMP = 15,
    VOICE_SET_COUNT = 16,
};

enum VoicePlayMode {
    VOICE_PLAY_IF_IDLE = 0,
    VOICE_PLAY_AFTER_GLOBAL_COOLDOWN = 1,
    VOICE_PLAY_INTERRUPT = 2,
};

class VoiceSet {
public:
    void initialize_voice_set(int count); // @ 0x448df0
    void shuffle_voice_set(); // @ 0x448e60
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
    void initialize_voice_manager(); // @ 0x448ee0
    void update_voice_manager(); // @ 0x4492a0
    bool play_voice_manager(
        int set_id, unsigned int mode, int sample_override); // @ 0x4492d0
    int is_voice_playing(); // @ 0x449410

    VoiceSet sets[VOICE_SET_COUNT]; // +0x000
    float global_progress;           // +0x180
    float global_frequency_seconds;  // +0x184
};

extern VoiceManager g_voice_manager; // unk_751498

typedef char VoiceSet_must_be_0x18[(sizeof(VoiceSet) == 0x18) ? 1 : -1];
typedef char VoiceManager_must_be_0x188[
    (sizeof(VoiceManager) == 0x188) ? 1 : -1];

#endif
