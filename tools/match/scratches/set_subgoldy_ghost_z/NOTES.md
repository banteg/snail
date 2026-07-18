# set_subgoldy_ghost_z @ 0x43d3d0

The helper is semantically pinned: it sets `SPRITE_FLAG_RENDER_ENABLED` on the
two cached SubGoldy ghost sprites at player offsets `+0x98` and `+0x9c`, then
writes the same ghost z into each sprite's `position.z` lane (`+0x50`). The
second pointer left in EAX is incidental; `update_subgoldy` immediately reloads
its game/root values and consumes no result.

2026-06-18 exact source-shape correction: spelling the z write as natural
`Sprite::position.z` float stores produces a 100% Wibo match. The old raw-dword
spelling was an unnecessary artifact from before the shared `Sprite` layout was
trusted.

Older near-match notes are retained below for audit history.

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
and the z store is a raw-bit write to `Sprite::position.z` (`+0x50`).
Rewriting the scratch to shared `player.h` + `sprite.h` keeps the exact same
91.43% residual.

2026-06-16 signature correction: the shared `player.h` declaration now takes a
`float payload`, matching the producer in `update_subgoldy`. The helper still
stores the z through an integer raw-bit view so the emitted code preserves
the native dword move into `Sprite::position.z`. Focused Wibo remains 91.43%,
and `update_subgoldy` remains 72.51%.

2026-06-16 five-target audit: focused Wibo still verifies 91.43%, 17/18
candidate/target insns, no masked operands, and the same final
`mov ecx, edx` residual. No source edit was accepted.

2026-06-18 naming sync: rejected the stale `TrackRowCell*` interpretation for
`Player +0x98/+0x9c`. The exact `initialize_subgoldy_ghost` scratch proves both
slots are allocated `Sprite*` values, and Binary Ninja/readback now names them
`ghost_sprite_a` and `ghost_sprite_b`.

2026-07-16 void ABI correction: `player.h`, this exact scratch, and both
decompiler replay catalogs now preserve `void __thiscall(Player*, float)`.
Removing the synthetic `return second` leaves the helper byte-exact at 18/18
instructions and leaves `update_subgoldy` unchanged at its honest 74.30%
baseline. The regenerated decompiles retain the real
`Player::ghost_sprite_a` / `Player::ghost_sprite_b` owners without pretending
the residual second pointer is a result.

## 2026-07-18 Sprite ownership replay

The focused lifecycle replay now verifies the exact void `Player*`/`float`
contract and loads the complete Sprite dependency in both decompilers. The
tracked artifacts expose both `ghost_sprite_*` owners, the shared render-enable
policy, and each `position.z` store. No matching source changed; the helper
remains exact at 18/18 instructions with no masked operands.
