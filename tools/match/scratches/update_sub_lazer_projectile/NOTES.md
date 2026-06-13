# Pinned — 41.73%, 127/127 insns (exact count, register/layout golf remains)

Semantics complete; key structural discoveries:

- the UPDATE state machine lives at +0x38 (1 live, 2 remove), distinct
  from the +0x80 pool-free flag the shoot scan tests — earlier reads
  conflated them
- both removal paths (state 2, and state 1 culled behind the owner kill
  plane at owner+0x2980) run the full list-remove + free-stack push
  (the same game+0x5a8 anchor the salt pool uses) and kill_sprite on
  the +0x64 handle — the remove block is duplicated in source
- the live path advances the wrapped sine bob: phase (+0x6c) += step
  (+0x70), wrap at 1.0, sprite local y (+0x4c) = sin(phase*2pi)*0.3 +
  base (+0x14)
- no position integration here — the projectile body motion belongs to
  the renderable-body owner linked at spawn

2026-06-13 pin audit: focused matcher still verifies 41.73%, 127/127 insns.
Keep pinned; state layout, duplicated remove paths, sprite bob, and body-motion
ownership are recovered, with only register/layout golf remaining.
