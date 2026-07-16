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

## 2026-07-16 member ABI closure

All 21 helpers from `initialize_bass_audio_backend @ 0x449460` through
`set_audio_normalization_scales @ 0x449be0` have exact C++ member scratches.
Windows callsites bind `ECX` to `g_audio_backend @ 0x753c58`; for example, the
RShell sample loaders, one-shot playback wrappers, volume-config calls, and
shutdown path all load that receiver immediately before their calls. This
proves that the receiver-unused bodies inferred as `stdcall` or `cdecl` are
still `AudioBackend` methods.

The narrow IDA/Binary Ninja replay now assigns those verified `__thiscall`
prototypes and imports the proven field prefix through `+0x18`. It deliberately
does not type the global data item as the complete struct: the known fields are
enough to recover method ownership, but no independent evidence yet proves the
object's tail boundary.
