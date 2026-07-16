# play_sound_effect_backend @ 0x432df0

Shared sound-effect playback wrapper.

- Focused Wibo result: 2026-06-18, 100.00%, 42/42 instructions, masked
  operands 11 ok.
- Ignores sample id `-1`.
- Multiplies requested gain by `g_audio_backend_sfx_normalization_scale`
  (`AudioBackend::sfx_normalization_scale` at `g_audio_backend + 0x10`).
- Chooses the lower registered-sample playback wrapper based on optional
  `pitch` and `pan` parameters.

## 2026-07-16 authored owner closure

iOS and both Android ABIs retain this entry point as
`RShellSoundPlay(int, float, float, float)` in `RShell.o`. The Android bodies
independently preserve the `sample_id == -1` sentinel, SFX-normalization
multiply, pitch/pan default branches, and platform sample dispatch. Windows
callers discard the backend result, so the proof-grade Windows public surface
remains `void` while the shared four-argument ownership is recovered. The exact
scratch remains 42/42 with 11 masked operands.
