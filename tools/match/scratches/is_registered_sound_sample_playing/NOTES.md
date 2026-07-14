# AudioBackend::is_registered_sound_sample_playing @ 0x449a40

The native voice-state caller loads `ECX = 0x753c58` immediately before the
call and tests `AL`, proving both the `AudioBackend` receiver and boolean return
surface. The method returns true only for the BASS active-state value `1`.
