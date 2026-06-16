# play_voice_manager / VoiceManager type consolidation

2026-06-16 shared-header slice:

- BN `VoiceSet` is 0x18: `sample_count`, `next_index`, `playlist`,
  `bites`, `cooldown`, `cooldown_step`.
- BN `VoiceManager` is 0x188: `VoiceSet sets[16]`, `global_progress`,
  `global_frequency_seconds`.
- The shared `voice_manager.h` preserves the exact helper matches and the
  smaller callsite migrations checked so far.
- `update_subgoldy` intentionally keeps its compact local `VoiceManager` call
  view. Including `voice_manager.h` preserved the headline score but changed
  the masked audit from 291 ok / 0 mismatch to 290 ok / 1 jump-table mismatch,
  so that scratch is not ready for this shared type yet.
