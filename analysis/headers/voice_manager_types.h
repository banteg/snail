#ifndef VOICE_MANAGER_TYPES_H
#define VOICE_MANAGER_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for Voice.o. The symbol-preserving
 * mobile builds retain cRVoiceSet/cRVoiceManager and the shared gVoiceManager
 * owner. Windows keeps 16 inline 0x18-byte VoiceSet records in one exact
 * 0x188-byte VoiceManager.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct VoiceSet {
    uint32_t sample_count;
    uint32_t next_index;
    int32_t* playlist;
    int32_t* bites;
    float cooldown;
    float cooldown_step;
} VoiceSet;

typedef struct VoiceManager {
    VoiceSet sets[16];
    float global_progress;
    float global_frequency_seconds;
} VoiceManager;

extern VoiceManager g_voice_manager;

#endif
