// Sound-effect manager call surface, partial. iOS names the same owner cRSound
// and the shared instance gRSound.
#ifndef SOUND_EFFECT_MANAGER_H
#define SOUND_EFFECT_MANAGER_H

struct tVector;
typedef tVector Vector3;

// Windows layout of one authored cRSoundBank entry. The shipped global holds
// 51 samples followed by one entry whose path points at an empty string.
struct cRSoundBank {
    char* path;               // +0x00
    int sample_id;            // +0x04, populated by Init
    int normalization_class;  // +0x08
};

typedef cRSoundBank SoundBankEntry;

enum {
    SOUND_BANK_LIVE_ENTRY_COUNT = 51,
    SOUND_BANK_ENTRY_COUNT = SOUND_BANK_LIVE_ENTRY_COUNT + 1,
};

class cRSound {
public:
    void Init(cRSoundBank* entries);              // @ 0x44dcb0
    void Play(int sound_id);                     // @ 0x44dde0
    void PlayVolume(int sound_id, float gain);   // @ 0x44de00
    void Play(int sound_id, tVector& position);  // @ 0x44dce0
    int PlayLooped(int sample_id); // @ 0x44de20
    void StopLooped(int handle);   // @ 0x44de30
};

typedef cRSound SoundEffectManager;

extern cRSound g_sound_effect_manager;
extern cRSoundBank
    g_sound_bank_entries[SOUND_BANK_ENTRY_COUNT]; // 0x4a2140, Android gSFXBank

typedef char cRSoundBank_must_be_0x0c[
    (sizeof(cRSoundBank) == 0x0c) ? 1 : -1];
typedef char SoundEffectManager_must_be_0x01[
    (sizeof(cRSound) == 0x01) ? 1 : -1];

#endif
