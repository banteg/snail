# Dossier — gates decoded via the campaign layout work (2026-06-12)

update_damage_gauge @ 0x440fd0. The former root-offset window is now fully
owned by `GameRoot::subgame` and its embedded `Player`:

- `Game+0x74621` is `SubgameRuntime::subgame_pause_gate`.
- Warning start is blocked by `Player::attachment_exit_pending` at `+0x41d`
  or `Player::completion_handoff_active` at `+0x440`; the latter also forces
  the accelerated drain path.
- `Game+0x42fde8 == 0.49f` is
  `Player::live_matrix.position.y == rest height`, so the
  transition into state 2 is grounded-player behavior.
- state-2 drain refreshes change_snail_skin(1, 0.2) per tick (matches
  the Zig controller's state-2 skin refresh)
- The three non-fill exits are `Player::completion_handoff_timer` at `+0x444`,
  `Player::resurrect_progress` at `+0x8c`, and
  `Player::presentation.cutscene.state` at presentation `+0x1964`.

Zig verify: gameplay/damage.zig models these as opaque UpdateContext
bools (warning_start_blocked, accelerated_drain_gate, suspended) — the
correct seam shape; they can now be WIRED to their real sources
(attachment exit, completion handoff, grounded/resurrection/cutscene state)
when cluster-5 routes.

## Scratch status

Promoted to a matcher scratch on 2026-06-13. Current result: 65.92%,
266/268 instructions. The first scratch is structure-first and covers:

- pause gate `Game::pause_gate` at +0x74621
- display-fill smoothing and hit-flash progress wrap
- state 0 warning start gates at `Game+0x430199` and `Game+0x4301bc`
- state 1 transition to drain on `Game+0x42fde8 == 0.49f`
- state 2 skin refresh, forced/unforced drain deltas, warning stop/sample
  stop exit conditions
- HUD mask/fill/flash quads with the native 560/70/64/396 geometry and one
  reused stack color

2026-06-13 follow-up: rewriting the state dispatch as a real `switch`
matches the native state-2-first fallthrough layout and raises the scratch
from 65.92% to 77.53%. Staging the skin-transition owner and calling
`stop_warning_sample` as a `Warning` method (the callee ignores `ecx`,
but the native callsite sets it up from `g_game+0x430170`) raises the result
to 80.60% with exact instruction count parity, 268/268.

Remaining diff is mostly x87/local scheduling and small register choices:
native uses stack slots `esp+4`/`esp+8`/`esp+0xc` for alpha, mask height, and
color, compares one ground-height field directly from memory, and computes the
second warning-method call address with `lea`. A render-local declaration-order
experiment and a pointer-local warning call were tested and produced no score
movement; do not use fake labels or volatile locals just to coerce those
layouts.

2026-06-13 tooling recheck: swapping the source declarations for `alpha` and
`mask_height` still emits identical 80.60% code in the current checkout, even
though the addressed dump shows those two stack slots are swapped versus
native. Treat the render-slot mismatch as allocation/scheduling until a
source-shaped owner changes codegen.

2026-06-16 type consolidation: `DamageGuage` is now shared through
`damage_guage.h` with initialize and apply-delta. The +0x24/+0x28 fields keep
the update-path `hit_flash_progress`/`hit_flash_step` names; apply-delta uses
the same pair as its retrigger gate. Match remains 80.60%.

2026-06-16 warning actor consolidation: the warning calls now use the shared
`Warning` view. `stop_warning_sample` stays declared as a method view here
because the native callsite sets `ecx` to `g_game+0x430170`, while the callee
ignores it. Match remains 80.60%.

2026-06-16 five-target audit: focused Wibo still verifies 80.60%, 268/268
insns, with 58 masked operands OK and no unresolved or mismatched operands.

2026-06-20 volatile audit: spelling direct `g_game` as a normal external (not
`volatile`) improves focused Wibo from 80.60% to 88.97% and extends the prefix
to 121/268. Reordering the mask-height thresholds to test the full-fill case
first, then spelling the flash-alpha ladder as the high-fill branch first,
raises the scratch to 93.08%, 267/268 insns, prefix 122/268, with 63 masked
operands OK and no unresolved or mismatched operands.

Rejected in this pass: swapping the `alpha`/`mask_height` declarations, moving
`Color4f color`, and splitting `mask_v` into a separate render local were all
neutral after the accepted branch order. The remaining first mismatch is still
a stack-slot allocation residual (`mask_height` at candidate `esp+4` versus
native `esp+8`, with `alpha` mirrored), followed by x87/render scheduling.

2026-06-20 render-tail audit: making the flash pulse an explicit source local
matches the decompiler-backed native intermediate `(sine(pulse * tau) + 1) *
0.5` and improves focused Wibo to 94.03%, 268/268 instructions, prefix
122/268, with 65 masked operands OK. This recovers instruction-count parity and
removes the earlier branch-label drift around the flash quad, but the first
residual remains the same mirrored `mask_height`/`alpha` stack-slot allocation.
Retested `alpha`/`mask_height` declaration order, `mask_v` hoisting, `Color4f`
hoisting, and an initialized `alpha` local; all were neutral at 94.03%, so keep
only the `flash_pulse` source split.

2026-06-21 root-view naming: the scratch-local root object slice was renamed
`DamageGaugeGameView` instead of generic `Game`; focused Wibo remained 94.03%.

2026-07-11 ownership closure: the synthetic root view is removed. Every field
lands inside `GameRoot::subgame.embedded_player()` or the subgame pause gate;
the completion-handoff timer pair is promoted into the shared `Player`, and the
last exit word is the already-owned `CutScene::state`. The live Binary Ninja
`Player` type now also exposes its progress bar, warning, lives, and borrowed
`SubgameRuntime*` backlink. Focused Wibo remains 94.03%, 268/268 instructions,
prefix 122/268, with 65 clean masked operands.

2026-07-11 authored-owner recovery: Android `cRDamageGuage::AI()` reads the
same +0x00..+0x28 field range and calls `cRDamageGuage::Take(float, bool)` on
the same receiver; `cRSubGoldy::AI()` calls it through the embedded +0x3c4
object. This maps mobile `AI()` here, correcting the former false association
with the separate Windows jetpack controller at player +0x2750. The shared
owner now keeps the shipped `Guage` spelling. Focused Wibo remains an honest
94.03%, 268/268 instructions, with 65 clean masked operands.
