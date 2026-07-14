# play_warning_sample_backend

Exact five-instruction `SoundEffectManager` method at `0x44de20`. The caller
loads `g_sound_effect_manager @ 0x78ff88` into `ecx`, passes warning sample 50,
and consumes the returned live handle immediately.

The thin body needs no receiver fields and forwards to the registered-sample
backend, but the native caller proves the method ABI. Promoting the standalone
transcription preserves all 5/5 instructions and its resolved backend call.
