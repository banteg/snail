# Residual diff — 91.43%, 17/18 insns

The helper is semantically pinned: it sets sprite flag `0x40` on the two cached
track-pair sprites at player offsets `+0x98` and `+0x9c`, then writes the same
float payload's raw dword bits into each sprite's `position.z` lane (`+0x50`)
and returns the second sprite pointer.

The only miss is a register-copy artifact before the second payload store. The
target copies the payload from `edx` to `ecx` and stores from `ecx`; VC6.5 emits
the equivalent direct store from `edx`. Do not force this with a semantic no-op.

2026-06-14 breadth pass: localized diff still isolates the single final
`mov ecx, edx` residual. Rejected source-plausible trials because they emitted
the same 91.43% code: a named `second_payload` local, a comma-return assignment
expression, an inline `set_payload` member on one or both stores, a pointer to
the second payload lane, and a reference alias for the second sprite. Keep the
clear pointer-local baseline unless original-source evidence explains the
native register copy.

2026-06-16 type correction: the old scratch-local `TrackPairSprite` was only a
misleading prefix view. The two pointers are the shared `Player::ghost_sprite_a`
and `Player::ghost_sprite_b` slots initialized by `initialize_subgoldy_ghost`,
and the payload store is a raw-bit write to `Sprite::position.z` (`+0x50`).
Rewriting the scratch to shared `player.h` + `sprite.h` keeps the exact same
91.43% residual.

2026-06-16 signature correction: the shared `player.h` declaration now takes a
`float payload`, matching the producer in `update_subgoldy`. The helper still
stores the payload through an integer raw-bit view so the emitted code preserves
the native dword move into `Sprite::position.z`. Focused Wibo remains 91.43%,
and `update_subgoldy` remains 72.51%.

2026-06-16 five-target audit: focused Wibo still verifies 91.43%, 17/18
candidate/target insns, no masked operands, and the same final
`mov ecx, edx` residual. No source edit was accepted.
