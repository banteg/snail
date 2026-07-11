# play_slug_voice

`play_slug_voice` @ 0x43f560 is exact at 22/22 instructions with three clean
masked operands. Android retains `cRSlug::VoicePlay(int)` and the same two-level
gate: the per-slug cooldown and shared `cRSlugVoiceManager` must both be idle;
success latches both, resets progress, and calls the voice backend.

The Windows shared manager lives at root `+0x3d0194`, exactly
`GameRoot::subgame +0x35bb7c`. The raw root reloads remain in this exact scratch
because they reproduce the native access schedule; ownership is recorded by
the shared `SubgameRuntime::slug_voice_manager` field.
