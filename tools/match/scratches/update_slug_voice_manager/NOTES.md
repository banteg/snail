# update_slug_voice_manager

`update_slug_voice_manager` @ 0x43f5e0 is exact at 15/15 instructions with two
clean masked operands. Android retains the authored member as
`cRSlugVoiceManager::AI()`: both advance positive progress by the stored step
and clear progress plus the active byte after it passes one. `update_subgame`
calls the embedded `SubgameRuntime::slug_voice_manager` directly.

The paired BN/IDA replay now types the receiver as `SlugVoiceManager*`, and the
tracked `update_subgame` artifact passes `&game->slug_voice_manager` without the
former `float*`/first-field cast. The exact matcher source remains unchanged.
