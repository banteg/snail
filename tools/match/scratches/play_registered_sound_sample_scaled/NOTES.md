# AudioBackend::play_registered_sound_sample_scaled @ 0x4499a0

All three native callers load `ECX = 0x753c58` immediately before the call,
proving that this exact helper is an `AudioBackend` method on
`g_audio_backend`, not a standalone stdcall function. The receiver is unused;
the method resolves a sample id through the registered-handle table and applies
the normalized volume to the BASS backend.
