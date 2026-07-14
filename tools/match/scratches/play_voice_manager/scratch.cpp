// play_voice_manager @ 0x4492d0 (thiscall, ret 0xc)

#include "audio_system.h"
#include "voice_manager.h"

bool VoiceManager::play_voice_manager(
    int set_id, unsigned int mode, int sample_override)
{
    bool played;
    if (mode != VOICE_PLAY_IF_IDLE) {
        if (mode != VOICE_PLAY_AFTER_GLOBAL_COOLDOWN) {
            if (mode == VOICE_PLAY_INTERRUPT) {
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
    if (played == true
            && (mode == VOICE_PLAY_AFTER_GLOBAL_COOLDOWN
                || mode == VOICE_PLAY_INTERRUPT)) {
        global_progress = 0.0f;
    }
    return played;

check_current_voice:
    if (is_voice_playing() != -1) {
        return false;
    }
    if (mode == VOICE_PLAY_AFTER_GLOBAL_COOLDOWN
            && global_progress < global_frequency_seconds) {
        return false;
    }
    goto play_selected_voice;
}
