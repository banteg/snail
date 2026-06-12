// set_audio_normalization_scales @ 0x449be0 (thiscall, ret 0xc)

class AudioBackend {
public:
    void set_audio_normalization_scales(float music_scale, float sfx_scale, float voice_scale);

    char pad_00[0xc];
    float music_normalization_scale; // 0x0c
    float sfx_normalization_scale; // 0x10
    float voice_normalization_scale; // 0x14
};

void AudioBackend::set_audio_normalization_scales(
    float music_scale, float sfx_scale, float voice_scale)
{
    music_normalization_scale = music_scale;
    sfx_normalization_scale = sfx_scale;
    voice_normalization_scale = voice_scale;
}
