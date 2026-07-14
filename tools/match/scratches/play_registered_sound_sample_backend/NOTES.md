# AudioBackend::play_registered_sound_sample_backend @ 0x449a80

Both native callers load `ECX = 0x753c58` immediately before the call, proving
the `AudioBackend` member ABI. The third argument forwarded to BASS is the
frequency/pitch override; the old scratch-local `pan` name conflicted with both
the BASS signature and the separate panned helper.
