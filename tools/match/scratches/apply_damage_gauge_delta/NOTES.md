# Pinned — 78.92%, 91 candidate / 94 target insns (register/materialization residuals remain)

Semantics complete and they REFINE the harvested hit-flash plan:

- gate: `(Player::movement_flags & 0x80) == 0 || force` — the sign bit, with
  force bypassing (`Player +0x338`, relocatable `Game +0x4300b4`)
- state 2 blocks unforced positive deltas; unforced negative deltas are
  also blocked while `Player::trampoline_bounce_active == 1`
  (`Player +0x1e4`, relocatable `Game +0x42ff60`)
- retrigger-gated side effects (timer at +0x24 zero, delta > 0):
  change_snail_skin(slot 1, 0.2s) on the owned `Player::presentation.snail_skin`
  child at `Game +0x434038`, voice 0 (damage) mode 1 seeding the timer on success;
  on FAILURE voice 9 (ouch) mode 0 (also seeding on success) and — only
  in this failure branch, gated on `Player::control_override_active` clear —
  the anim pair dispatch_cutscene_animation(6, immediate) then (1, queued) on
  `Player::presentation` at `Game +0x432700`
- fill at +0x1c accumulates the delta, clamped to [0, 1]
- collision callers feed -0.5 health, +0.04 garbage, +0.15 salt,
  +1.0 slug, +0.02 sub-lazer with force = 0

The Zig hit-flash wiring (checklist Phase 4 harvest) should be verified
against the corrected nesting: the anim dispatches belong inside the
voice-failure branch, not parallel to it.

2026-06-13 pin audit: focused matcher verified 58.20%, 95/94 insns.
Keep pinned; the remaining diff is register/materialization golf, while the
damage gates, fill clamp, voice fallback, and animation nesting are recovered.

2026-06-16 type consolidation: this now uses the shared
`DamageGuage` view from `damage_guage.h`. The former local
`retrigger_timer`/`retrigger_step` names are the same +0x24/+0x28
`hit_flash_progress`/`hit_flash_step` fields initialized and advanced by the
gauge update path. Focused Wibo now verifies 60.32%, 94 target / 95 candidate
insns, with 13 masked operands OK and one real constant relocation mismatch
in the clamp tail (`0.0f`/`1.0f` materialization differs from native).

2026-06-16 source-shape probes rejected: spelling the negative clamp as a
separate `updated = 0.0f; fill = updated;` local produced identical 60.32%
code, while hoisting `g_game_base` into an early `game` local regressed the
score to 59.14%. Keep the shared type view and direct global-offset spelling.

2026-06-20 volatile-base audit: unlike the attachment-follow header case, this
scratch improves when `g_game_base` is a normal external. Focused Wibo moves
from 60.32% to 64.13% (90/94 candidate/target instructions). The change removes
several repeated volatile reloads while preserving the recovered damage gates
and side-effect nesting. The pass also corrected the fallback animation
suppress byte from the stale `Game+0x42ffd4` note to `Game+0x430054`, matching
Binja and the target dump at `0x4414b6`; the offset is now curated as
`g_damage_gauge_anim_suppress_offset`. The remaining masked debt is still the
known clamp-tail `0.0f` versus `1.0f` constant materialization mismatch. An
explicit `char* game_base` local with the non-volatile declaration regresses to
53.76% by adding another saved register and moving `this`, so the direct
global-offset spelling remains retained.

2026-06-21 clamp-tail pass: keeping the accumulated `updated` local as the
single final `fill` store improves focused Wibo to 72.43% (91/94 candidate/
target instructions) and clears the stale constant relocation mismatch; the
mask audit is now 18 clean operands. The retained source still matches the
native clamp semantics (`fill` is first written with the raw sum, then clamped
through `updated`). Rejected followups on top of this shape: explicit
`game_base` locals still regress badly, `state` snapshots regress, and
goto/common-flag spellings for the voice-success progress store are neutral or
worse.

2026-07-11 authored-owner recovery: Android and iOS identify this exact method
as `cRDamageGuage::Take(float, bool)`. Android calls it on the same 0x2c-byte
receiver from `cRDamageGuage::AI()` and `cRSubGoldy::Collision()`, confirming
both ownership and the force argument omitted by the old decompiler prototype.
The shared owner now keeps the shipped `Guage` spelling. Focused Wibo remains
an honest 72.43%, 91/94 instructions, with 18 clean masked operands.

2026-07-11 skin-owner consolidation: the global at game+0x434038 is now typed
as the exact 0x20-byte `cRSnailSkin` child rather than a local transition API.
Android's `cRSnailSkin::Change(int, float)` independently confirms this call;
the shared type substitution is codegen-neutral at the same honest 72.43%.

2026-07-12 Player-owner consolidation: the four former raw relocatable views
are all fields of the embedded `cRSubGoldy`: `movement_flags` at +0x338,
`trampoline_bounce_active` at +0x1e4, `control_override_active` at +0x2d8,
and the authored `cRSnail` presentation at +0x2984. The skin receiver is the
presentation's owned `cRSnailSkin` at +0x1938, hence `Player +0x42bc` and the
correct relocatable address `Game +0x434038` (the earlier +0x430938 comment
was a typo). The scratch now reaches every gate and side effect through the
shared `GameRoot -> SubgameRuntime -> Player` layout and removes the fake
`DamageSnailView`. That ownership substitution alone was codegen-neutral at
72.43%, so it is not presented as a score claim. Reorienting the same voice
fallback as `if (!play damage) { play ouch; animate; } else { seed timer; }`
then recovers the native failure-first layout without changing behavior.
Focused Wibo improves to 78.92%, 91/94 instructions, with all 20 masked
operands clean.
