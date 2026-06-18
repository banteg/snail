# play_sound_effect_backend @ 0x432df0

Shared sound-effect playback wrapper.

- Focused Wibo result: 2026-06-18, 100.00%, 42/42 instructions, masked
  operands 11 ok.
- Ignores sample id `-1`.
- Multiplies requested gain by `g_audio_backend_sfx_normalization_scale`
  (`AudioBackend::sfx_normalization_scale` at `g_audio_backend + 0x10`).
- Chooses the lower registered-sample playback wrapper based on optional
  `pitch` and `pan` parameters.
