# update_invincible_shell @ 0x444b50

Exact source-shaped recovery of authored `cRInvincible::AI` on the 0xa4-byte
`Invincible` visual embedded at `Snail +0x1894`.

Recovered behavior:

- state 0 either starts the shell while `Player::movement_flags & 0x80` is
  active, or clears the embedded shell's inherited `list_flags & ~0x20`;
- state 1 fades in to `1.0` and moves to state 2, but drops to state 3 as soon
  as the invincible bit clears;
- state 2 waits for that bit to clear;
- state 3 fades out, restores base snail skin slot 0 at zero, and returns to
  state 0 once the fade goes below zero;
- active states advance `spin_phase`, apply invincible skin slot 2, write white
  color with alpha `fade_progress * 0.80000001`, copy
  inherited `Player::presentation.transform`, then rotate it around world Y by
  `spin_phase * 6.2831855`.

Focused Wibo result: exact 100%, 98/98 insns, 98/98 prefix, and 28 clean masked
operands. The exact match requires direct `Player::movement_flags` bit tests;
a helper function was source-clean but introduced calls and an extra saved
register, regressing to 68.39%.

Cross-port ownership is high confidence: Android exports `cRInvincible::AI`
and implements the same four-state fade/spin machine, skin transitions, color
alpha, and live-matrix rotation. iOS v1.5 exports the same method from
`SubGame.o`; iOS v1.9 retains the authored class, typeinfo, and vtable.

All shared accesses now follow the complete
`GameRoot -> SubgameRuntime -> Player -> Snail` owner graph: movement flags,
the embedded shell render node, `SnailSkin`, and the live presentation matrix.
The former five absolute root expressions disappear while the body stays
exact.

2026-07-14 renderable-owner closure: the copied presentation matrix is now
explicitly `Snail`'s inherited `RenderableBod::transform`. Focused Wibo remains
exact at 100.00%, 98/98 instructions, full prefix, and 28 clean operands.

2026-07-14 shell inheritance closure: the destination matrix and inherited
render fields now come from `Invincible`'s complete `RenderableBod` base rather
than a manually duplicated prefix. Focused Wibo remains byte-identical at
98/98 instructions with all 28 operands clean.
