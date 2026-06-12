# Pinned — 48.04%, 215/218 insns, register-allocation residual

Structure, control flow, and every constant align; the residual is a
zero-register materialization ripple (our build zeroes ebx early and
reuses it for null compares and state stores; the target uses immediate
zeros and test-based null checks), same class as mark_track_warning_zones.

Layout facts settled by this asm (ledgered 2026-06-12):

- velocity IS a float triple at +0x8c/+0x90/+0x94: update does
  `position += velocity` component-wise. spawn's `mov byte [+0x94], 1`
  pokes velocity.z's low byte — a native bug leaving z a denormal ~0.
- progress/step at +0x98/+0x9c reach PAST the 0x98 pool stride into the
  next slot's header dwords, and spawn never initializes them — the
  progress > 1.0 state-2 transition is driven by garbage that is almost
  always a denormal, so live salt effectively persists until collision,
  bounds exit, or kill-plane exit.
- state 2 inlines the full live-list removal (same machinery as
  deactivate_salt_hazard, early-return error shape, free-stack at
  game+0x5a8).
- state 1: progress accumulate, integrate, y >= 0 and
  z >= game[+0x3be0e4] kill plane, grid-cell tile 14 + y < 7 floor exit,
  then containment probes: primary (+0xa4) gated on cell flag 0x40,
  secondary (+0xa8) on flag 0x80, thiscall on [template+0x38] with
  by-value Vector3 args (probe = position+velocity, sweep = velocity*1.05),
  miss returns without deactivating; hit calls the 0x449c00 effect with a
  static arg then deactivates.
