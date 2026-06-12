# Pinned — 58.20%, 94/95 insns (first-pass scratch, register/volatile golf remains)

Semantics complete and they REFINE the harvested hit-flash plan:

- gate: `(game[0x4300b4] & 0x80) == 0 || force` — the sign bit, with
  force bypassing
- state 2 blocks unforced positive deltas; unforced negative deltas are
  also blocked while `game[0x42ff60] == 1` (a previously unknown global)
- retrigger-gated side effects (timer at +0x24 zero, delta > 0):
  change_snail_skin(slot 1, 0.2s) on the global transition at
  game+0x430938, voice 0 (damage) mode 1 seeding the timer on success;
  on FAILURE voice 9 (ouch) mode 0 (also seeding on success) and — only
  in this failure branch, gated on game[0x42ffd4] clear — the anim pair
  dispatch_cutscene_animation(6, immediate) then (1, queued) on the
  dispatcher at game+0x432680
- fill at +0x1c accumulates the delta, clamped to [0, 1]
- collision callers feed -0.5 health, +0.04 garbage, +0.15 salt,
  +1.0 slug, +0.02 sub-lazer with force = 0

The Zig hit-flash wiring (checklist Phase 4 harvest) should be verified
against the corrected nesting: the anim dispatches belong inside the
voice-failure branch, not parallel to it.
