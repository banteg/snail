// update_warning @ 0x446f80 (thiscall, ret)
// The damage-warning actor: state 1 holds the overlay alpha near full
// (0.99748... bits 1065336439) while the phase fills; state 2 fades the
// first half then holds zero, replaying sound 50 on wrap back to 1.

struct Game {
    char unknown_00[0x74621];
    unsigned char suspended; // +0x74621
};

extern Game* volatile g_game; // data_4df904

struct WarningTarget {
    char unknown_00[0x208];
    float overlay_alpha; // +0x208 (dword 130)
};

struct SoundEffectManager {
    void play_sound_effect(int sound_id);
};
extern SoundEffectManager g_sound_effect_manager;

struct WarningActor {
    void update_warning();

    int state;             // +0x00: 0 idle, 1 fill, 2 fade
    float phase;           // +0x04
    float phase_step;      // +0x08
    WarningTarget* target; // +0x0c
};

void WarningActor::update_warning()
{
    if (!g_game->suspended && state) {
        if (state == 1) {
            *(int*)&target->overlay_alpha = 1065336439;
            float advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = 2;
            }
        } else if (state == 2) {
            if (phase >= 0.5f)
                target->overlay_alpha = 0;
            else
                target->overlay_alpha = 1.0f - (phase + phase);
            float advanced = phase_step + phase;
            phase = advanced;
            if (advanced > 1.0f) {
                phase = 0.0f;
                state = 1;
                g_sound_effect_manager.play_sound_effect(50);
            }
        }
    }
}
