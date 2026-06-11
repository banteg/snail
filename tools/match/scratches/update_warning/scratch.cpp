// update_warning @ 0x446f80 (thiscall, ret)

extern char* g_game_base; // data_4df904

struct SoundEffectBackend {
    void play_sound_effect(int sound_id);
};

extern SoundEffectBackend g_sound_effect_backend;

struct FrontendWidget {
    char unknown_00[0x208];
    float hot_text_alpha; // +0x208
};

class WarningActor {
public:
    void update_warning();

    int state;                 // +0x00
    float progress;            // +0x04
    float progress_step;       // +0x08
    FrontendWidget* border;    // +0x0c
};

void WarningActor::update_warning()
{
    int zero = 0;
    if (*(unsigned char*)(g_game_base + 0x74621) != zero)
        return;

    switch (state - zero) {
    case 0:
        return;
        case 2:
            if (progress < 0.5f) {
                border->hot_text_alpha = 1.0f - (progress + progress);
            } else {
                border->hot_text_alpha = 0.0f;
            }

            progress = progress + progress_step;
            if (progress > 1.0f) {
                progress = 0.0f;
                state = 1;
                g_sound_effect_backend.play_sound_effect(0x32);
            }
            break;
        case 1:
            border->hot_text_alpha = 0.999000013f;
            progress = progress + progress_step;
            if (progress > 1.0f) {
                progress = 0.0f;
                state = 2;
            }
            break;
    }
}
