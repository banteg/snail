# play_sound_effect_scaled

Exact nine-instruction Windows
`SoundEffectManager::play_sound_effect_scaled(int, float)` at `0x44de00`. It
forwards the caller's gain while retaining default pitch `-1.0` and centered
pan `0.0`.

The Windows method receiver is supplied at callsites and the cross-port owner
is `cRSound::PlayVolume(int, float)`. Promoting the standalone transcription to
the shared owner preserves the exact 9/9 body and its resolved backend call.
