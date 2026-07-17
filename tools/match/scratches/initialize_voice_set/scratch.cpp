// initialize_voice_set @ 0x448df0 (thiscall, ret 0x4)

#include "voice_manager.h"

void* allocate_tracked_memory(int size, char* label);

void VoiceSet::initialize_voice_set(int count)
{
    sample_count = count;
    next_index = 0;
    playlist = (int*)allocate_tracked_memory(count * sizeof(*playlist), "Playlist");
    bites = (int*)allocate_tracked_memory(
        sample_count * sizeof(*bites), "VoiceBite");
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
    shuffle_voice_set();
}
