// is_voice_playing @ 0x449410 (thiscall, ret)

#include "voice_manager.h"

struct AudioBackend {
    bool is_registered_sound_sample_playing(int sample_id);
};

extern AudioBackend g_audio_backend; // 0x753c58

int VoiceManager::is_voice_playing()
{
    int set_index = 0;
    int* set = (int*)this;
    while (set_index < 16) {
        int bite_index = 0;
        if (*set > 0) {
            while (!g_audio_backend.is_registered_sound_sample_playing(*(int*)(set[3] + 4 * bite_index))) {
                ++bite_index;
                if (bite_index >= *set) {
                    goto next_set;
                }
            }
            return *(int*)(*((int*)this + 6 * set_index + 3) + 4 * bite_index);
        }

next_set:
        ++set_index;
        set += 6;
    }
    return -1;
}
