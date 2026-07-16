# play_voice_backend @ 0x432e80

Shared voice playback wrapper.

- Focused Wibo result: 2026-06-18, 100.00%, 42/42 instructions, masked
  operands 11 ok.
- Ignores sample id `-1`.
- Multiplies requested gain by `g_audio_backend_voice_normalization_scale`
  (`AudioBackend::voice_normalization_scale` at `g_audio_backend + 0x14`).
- Uses the same optional `pitch` and `pan` dispatch as the SFX backend wrapper.

## 2026-07-16 authored owner closure

iOS and both Android ABIs retain this entry point as
`RShellVoicePlay(int, float, float, float)` in `RShell.o`. The Android bodies
independently preserve the `sample_id == -1` sentinel, voice-normalization
multiply, pitch/pan default branches, and platform sample dispatch. Windows
callers discard the backend result, so the proof-grade Windows public surface
remains `void` while the shared four-argument ownership is recovered. The exact
scratch remains 42/42 with 11 masked operands.
