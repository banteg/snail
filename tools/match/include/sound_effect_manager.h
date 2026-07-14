// Sound-effect manager call surface, partial. iOS names the same owner cRSound
// and the shared instance gRSound.
#ifndef SOUND_EFFECT_MANAGER_H
#define SOUND_EFFECT_MANAGER_H

struct Vector3;

// Windows layout of one authored cRSoundBank entry. The shipped global holds
// 51 samples followed by one entry whose path points at an empty string.
struct SoundBankEntry {
    char* path;               // +0x00
    int sample_id;            // +0x04, populated by initialize_sound_bank
    int normalization_class;  // +0x08
};

enum {
    SOUND_BANK_LIVE_ENTRY_COUNT = 51,
    SOUND_BANK_ENTRY_COUNT = SOUND_BANK_LIVE_ENTRY_COUNT + 1,
};

class SoundEffectManager {
public:
    char* initialize_sound_bank(SoundBankEntry* entries); // @ 0x44dcb0
    void play_sound_effect(int sound_id); // @ 0x44dde0
    void play_sound_effect_scaled(int sound_id, float gain); // @ 0x44de00
    void play_sound_effect_at_position(
        int sound_id, Vector3& position); // @ 0x44dce0
    int play_warning_sample_backend(int sample_id);
    void stop_warning_sample_handle(int handle);
};

extern SoundEffectManager g_sound_effect_manager;
extern SoundBankEntry
    g_sound_bank_entries[SOUND_BANK_ENTRY_COUNT]; // 0x4a2140, Android gSFXBank

typedef char SoundBankEntry_must_be_0x0c[
    (sizeof(SoundBankEntry) == 0x0c) ? 1 : -1];

#endif
