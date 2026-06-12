// set_global_sample_volume_config @ 0x449b50 (thiscall, ret 0x4)

typedef int (__stdcall* BassSetConfigFn)(int option, int value);

extern BassSetConfigFn g_bass_set_config; // 0x753c1c

class AudioBackend
{
public:
    int set_global_sample_volume_config(float volume);
};

int AudioBackend::set_global_sample_volume_config(float volume)
{
    return g_bass_set_config(4, (int)(volume * 100.0f));
}
