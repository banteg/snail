# AudioBackend::play_registered_sound_sample_scaled_panned @ 0x449ae0

Both native callers load `ECX = 0x753c58` immediately before the call, proving
the `AudioBackend` member ABI. This variant forwards independent pitch and pan
overrides after applying the supplied normalized volume.
