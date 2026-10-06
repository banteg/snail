// set_audio_normalization_scales @ 0x449be0 (thiscall, ret 0xc)

#include "audio_system.h"

void AudioBackend::set_audio_normalization_scales(
    float music_scale, float sfx_scale, float voice_scale)
{
    music_normalization_scale = music_scale;
    sfx_normalization_scale = sfx_scale;
    voice_normalization_scale = voice_scale;
}
