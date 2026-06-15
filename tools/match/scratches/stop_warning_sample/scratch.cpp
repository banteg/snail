// stop_warning_sample @ 0x446f60 (cdecl, ret)

struct WarningSampleBackend {
    int play_warning_sample_backend(int sample_id);
    void stop_warning_sample_handle(int handle);
};

extern WarningSampleBackend g_sound_effect_manager;

void stop_warning_sample()
{
    int handle = g_sound_effect_manager.play_warning_sample_backend(0x32);
    g_sound_effect_manager.stop_warning_sample_handle(handle);
}
