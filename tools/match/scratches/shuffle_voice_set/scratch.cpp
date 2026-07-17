// shuffle_voice_set @ 0x448e60 (thiscall, ret)

#include "voice_manager.h"

int next_math_random_value();

void VoiceSet::shuffle_voice_set()
{
    int remaining = 100;
    int second_index;
    do {
        int first_index = (int)((float)next_math_random_value() * (float)sample_count * 0.000030517578f);
        second_index = (int)((float)next_math_random_value() * (float)sample_count * 0.000030517578f);
        int* list = playlist;
        --remaining;
        int second_value = list[second_index];
        int first_value = list[first_index];
        list[first_index] = second_value;
        playlist[second_index] = first_value;
    } while (remaining != 0);
}
