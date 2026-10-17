// cRSound::Init @ 0x44dcb0 (thiscall, ret 0x4)

#include "rshell.h"
#include "sound_effect_manager.h"

void cRSound::Init(cRSoundBank* entries)
{
    cRSoundBank* cursor = entries;
    char* result = cursor->path;

    if (*result != 0) {
        cRSoundBank* store = entries;
        do {
            store->sample_id = register_sound_sample(result, store->normalization_class);
            cursor += 1;
            store = cursor;
            result = cursor->path;
        } while (*result != 0);
    }
}
