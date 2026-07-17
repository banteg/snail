#ifndef SOUND_EFFECT_MANAGER_TYPES_H
#define SOUND_EFFECT_MANAGER_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the Windows cRSound facade and
 * its shipped cRSoundBank table. The Windows manager has no fields and uses
 * the one-byte empty-class extent; Android later stores a bank pointer in its
 * platform-specific owner.
 */

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct SoundEffectManager {
    uint8_t empty_object;
} SoundEffectManager;

typedef struct SoundBankEntry {
    char* path;
    int32_t sample_id;
    int32_t normalization_class;
} SoundBankEntry;

extern SoundEffectManager g_sound_effect_manager;
extern SoundBankEntry g_sound_bank_entries[52];

#endif
