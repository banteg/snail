// play_voice_manager @ 0x4492d0 (thiscall, ret 0xc)

struct AudioBackend {
    void stop_registered_sound_sample(int sample_id);
};

extern AudioBackend g_audio_backend; // 0x753c58

class VoiceSet {
public:
    bool play_voice_set(int sample_override);

    char unknown_00[0x18];
};

class VoiceManager {
public:
    bool play_voice_manager(int set_id, unsigned int mode, int sample_override);
    int is_voice_playing();

    VoiceSet sets[16];              // +0x000
    float global_progress;           // +0x180
    float global_frequency_seconds;  // +0x184
};

bool VoiceManager::play_voice_manager(int set_id, unsigned int mode, int sample_override)
{
    bool played;
    if (mode != 0) {
        if (mode != 1) {
            if (mode == 2) {
                int playing_sample = is_voice_playing();
                if (playing_sample != -1) {
                    g_audio_backend.stop_registered_sound_sample(playing_sample);
                }
            }
            goto play_selected_voice;
        }
    }
    goto check_current_voice;

play_selected_voice:
    played = sets[set_id].play_voice_set(sample_override);
    if (played == true && (mode == 1 || mode == 2)) {
        global_progress = 0.0f;
    }
    return played;

check_current_voice:
    if (is_voice_playing() != -1) {
        return false;
    }
    if (mode == 1 && global_progress < global_frequency_seconds) {
        return false;
    }
    goto play_selected_voice;
}
