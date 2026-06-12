// is_registered_sound_sample_playing @ 0x449a40 (stdcall, ret 0x4)

typedef int (__stdcall* BassSampleIsActiveFn)(int sample_handle);

extern int g_registered_sound_sample_handles[];       // 0x7537e0
extern BassSampleIsActiveFn g_bass_sample_is_active;  // 0x753ca8

unsigned char __stdcall is_registered_sound_sample_playing(int sample_id)
{
    unsigned char active = g_bass_sample_is_active(g_registered_sound_sample_handles[sample_id]) == 1;
    return active;
}
