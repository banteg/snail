// initialize_sound_bank @ 0x44dcb0 (thiscall, ret 0x4)

#include "sound_effect_manager.h"

int register_sound_sample(char* path, int normalization_class);

char* SoundEffectManager::initialize_sound_bank(SoundBankEntry* entries)
{
    SoundBankEntry* cursor = entries;
    char* result = cursor->path;

    if (*result != 0) {
        SoundBankEntry* store = entries;
        do {
            store->sample_id = register_sound_sample(result, store->normalization_class);
            cursor += 1;
            store = cursor;
            result = cursor->path;
        } while (*result != 0);
    }

    return result;
}
