// AudioBackend::stop_registered_sound_sample @ 0x449a20

#include "audio_system.h"

typedef int (__stdcall* BassSampleStopFn)(int sample_handle);

extern int g_registered_sound_sample_handles[]; // 0x7537e0
extern BassSampleStopFn g_bass_sample_stop;     // 0x753c94

void AudioBackend::stop_registered_sound_sample(int sample_id)
{
    g_bass_sample_stop(g_registered_sound_sample_handles[sample_id]);
}
