# Pinned — 72.44%, 127/127 insns, layout-only residual

Semantics complete; key structural discoveries:

- the UPDATE state machine lives at +0x38 (1 live, 2 remove), distinct
  from the +0x80 pool-free flag the shoot scan tests — earlier reads
  conflated them
- both removal paths (state 2, and state 1 culled behind the owner kill
  plane at owner+0x2980) run the full list-remove + free-stack push
  (the same game+0x5a8 anchor the salt pool uses) and kill_sprite on
  the +0x64 handle — the remove block is duplicated in source
- the live path advances the wrapped sine bob: phase (+0x6c) += step
  (+0x70), wrap at 1.0, `sprite->position.y` (+0x4c) =
  sin(phase*2pi)*0.3 + base (+0x14)
- no position integration here — the projectile body motion belongs to
  the renderable-body owner linked at spawn

2026-06-15 pin audit: focused matcher verifies 72.44%, 127/127 insns, masked
operands 15 ok / 0 mismatch. Source now uses the sibling pickup state-machine
shape, `Sprite::kill_sprite()` member calls, the raw `g_game_base + 0x5a8`
free-list anchor, and the strict `> 1.0f` bob wrap compare. Keep pinned; the
remaining diff is block layout/register allocation, not a semantic gap.

2026-06-16 type split: promoted the update object into
`SubLazerRuntime` in `sub_lazer_types.h` and kept it distinct from the
`SubLazerSlot` pool-spawn view. The cull plane now reads shared
`Player::interaction_max_z` at `+0x2980`; the match remains 72.44%. BN's
current `SubLazerSlot*` parameter name for this update is misleading for the
local matched layout.
