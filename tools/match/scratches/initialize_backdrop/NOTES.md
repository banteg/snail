# initialize_backdrop @ 0x410e20

Exact match: 100.00% (55 target insns, 55 candidate insns), clean masks.

Seeds the shared backdrop controller and primes the distortion grid.

Recovered layout:

- `BackdropDistortCell` is a six-float record: `phase`, `phase_step`, source
  x/y amplitude, and per-frame current x/y offsets.
- `+0x65c..+0x678` and `+0x6bc..+0x6c4` are now typed in
  `Backdrop` because initialization writes them, but they deliberately remain
  `unknown_<offset>` until another user proves semantics.
- `+0x67c..+0x69b` and `+0x69c..+0x6bb` are two owned
  `BackdropWorldBlend` records. Each contains a constructed `tColour`, blend
  fraction, blend step, previous world, and current world.

Open evidence: the only known caller passes `last_mode == 1`, but native still
contains a distinct `last_mode != 0 && last_mode != 1` path that skips the
world-blend reset before selecting world `0` and clearing distort.

Source-shape note: the native `last_mode` dispatch is VC6's two-case `switch`
idiom (`sub eax, ebx; je; dec eax; jne`), not a plain `if`/`else if` chain.
The scratch also keeps the reused `0x3f800000` value as raw bits because native
stores that same register into `unknown_664`, `primary_world_blend.blend`, and
`secondary_world_blend.blend`.

2026-07-14 authored world-blend ownership: Android preserves
`cRBackdrop::SetWorld(int)` at `0x31980`. Its complete body performs the same
seven field operations as Windows `0x410f40`, at mobile offsets `+0xb4..+0xe0`:
it inverts each blend fraction, shifts each current world into its previous
slot, and installs the argument as both current worlds. The identical repeated
layout proves the two 0x20-byte Windows records rather than merely suggesting
names from adjacency. Both Windows callers discard EAX, and changing the
Windows method to `void` remains exact at 14/14 instructions.
