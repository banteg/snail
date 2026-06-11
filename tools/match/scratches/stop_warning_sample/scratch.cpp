// stop_warning_sample @ 0x446f60 (cdecl, ret)

struct WarningSampleBackend {
    int play_warning_sample_backend(int sample_id);
    void stop_warning_sample_handle(int handle);
};

extern WarningSampleBackend g_warning_sample_backend;

void stop_warning_sample()
{
    int handle = g_warning_sample_backend.play_warning_sample_backend(0x32);
    g_warning_sample_backend.stop_warning_sample_handle(handle);
}
