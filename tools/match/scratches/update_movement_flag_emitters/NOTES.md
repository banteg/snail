# update_movement_flag_emitters @ 0x43a300

Exact match: 100.00%, 39/39 instructions.

This helper dispatches Golb creation from the player emitter bank:

- classifies `player+0x338` movement flags into a spawn budget of 1, 2, or 3;
- scans 12 emitter slots at `this+0x450` with stride `0x2e8`;
- calls `create_golb(owner, spawn_count, slot_index)` only for inactive slots;
  and
- stops once the spawn budget is exhausted, or after all slots are scanned.

The flag families are `(flags & 0x69) -> 1`, `(flags & 0x12) -> 2`, and
`(flags & 4) -> 3`; no slots are touched when none of those families are set.

The exact source shape uses nested false-body loops for the flag classifier.
That gives VC6 the native `test; jne out-of-line assignment` layout for the
one-shot and two-shot families while keeping the shared spawn loop readable.

2026-06-17 naming correction: the method owner is now
`PlayerGolbEmitterView`, with compact `GolbEmitterSlot` entries at
`this+0x450`. The previous local `GolbShot` owner name made the type report
look worse than the evidence: this helper proves the projectile slot stride and
`state +0x244`, but `this` is the player-side emitter bank. Focused Wibo stays
exact at 39/39 instructions.
