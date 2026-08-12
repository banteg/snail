# play_warning_sample_backend

Exact five-instruction `SoundEffectManager` method at `0x44de20`. The caller
loads `g_sound_effect_manager @ 0x78ff88` into `ecx`, passes warning sample 50,
and consumes the returned live handle immediately.

The thin body needs no receiver fields and forwards to the registered-sample
backend, but the native caller proves the method ABI. Promoting the standalone
transcription preserves all 5/5 instructions and its resolved backend call.

## 2026-08-12 authored method recovery

iOS retains this exact source method as `cRSound::PlayLooped(int)` in
`RSound.o`. Its body forwards to `RShellSoundPlayLooped(int)`, just as Windows
forwards to `play_registered_warning_sample`, the already-recovered Windows
RShellSoundPlayLooped entry point. The iOS decompiler gives the method a stale
void prototype, but `cRDamageGuage::AI` immediately assigns its R0 result and
passes that live handle to `cRSound::StopLooped(int)`, exactly matching the
Windows warning call chain. The source-facing scratch now emits the recovered
VC6 `?PlayLooped@cRSound@@QAEHH@Z` symbol; the stable matcher ID is retained.
