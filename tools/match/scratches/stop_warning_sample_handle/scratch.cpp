// stop_warning_sample_handle @ 0x44de30 (stdcall, ret 0x4)

void stop_registered_sound_sample(int handle); // sub_432de0

void __stdcall stop_warning_sample_handle(int handle)
{
    stop_registered_sound_sample(handle);
}
