# set_audio_normalization_scales / AudioBackend type consolidation

2026-06-16 shared-header slice:

- `AudioBackend +0x00` is the music-stream active byte used by
  `stop_music_stream`.
- `AudioBackend +0x0c/+0x10/+0x14` are the music, SFX, and voice
  normalization scales written here.
- `AudioBackend +0x18` is the pause latch used by
  `resume_audio_backend_if_paused` and `pause_audio_backend_if_running`.
- Gameplay callsites still spell some global registered-sample helpers as
  `g_audio_backend` member calls because that preserves their native thiscall
  shape.
- `SoundEffectManager` is method-only for now. `add_subgoldy_score` and
  `update_subgoldy` keep compact local sound views because including
  `audio_system.h` regresses their jump-table masked operand audit.
