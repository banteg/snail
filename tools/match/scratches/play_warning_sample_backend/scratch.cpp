// play_warning_sample_backend @ 0x44de20 (stdcall, ret 0x4)

int play_registered_warning_sample(int sample_id);

int __stdcall play_warning_sample_backend(int sample_id)
{
    return play_registered_warning_sample(sample_id);
}
