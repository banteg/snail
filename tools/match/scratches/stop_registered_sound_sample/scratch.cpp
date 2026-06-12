// stop_registered_sound_sample @ 0x449a20 (stdcall, ret 0x4)

typedef int (__stdcall* BassSampleStopFn)(int sample_handle);

extern int g_registered_sound_sample_handles[]; // 0x7537e0
extern BassSampleStopFn g_bass_sample_stop;     // 0x753c94

int __stdcall stop_registered_sound_sample(int sample_id)
{
    return g_bass_sample_stop(g_registered_sound_sample_handles[sample_id]);
}
