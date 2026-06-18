# play_voice_backend @ 0x432e80

Shared voice playback wrapper.

- Focused Wibo result: 2026-06-18, 100.00%, 42/42 instructions, masked
  operands 11 ok.
- Ignores sample id `-1`.
- Multiplies requested gain by `g_audio_backend_voice_normalization_scale`
  (`AudioBackend::voice_normalization_scale` at `g_audio_backend + 0x14`).
- Uses the same optional `pitch` and `pan` dispatch as the SFX backend wrapper.
