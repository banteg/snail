# initialize_backdrop @ 0x410e20

Exact match: 100.00% (55 target insns, 55 candidate insns), clean masks.

Seeds the shared backdrop controller and primes the distortion grid.

Recovered layout:

- `BackdropDistortCell` is a six-float record: `phase`, `phase_step`, source
  x/y amplitude, and per-frame current x/y offsets.
- `+0x65c..+0x678` and `+0x6bc..+0x6c4` are now typed in
  `Backdrop` because initialization writes them, but they deliberately remain
  `unknown_<offset>` until another user proves semantics.
- `primary_blend_step +0x690` and `secondary_blend_step +0x6b0` are float
  transition steps, not integer bit lanes.

Open evidence: the only known caller passes `last_mode == 1`, but native still
contains a distinct `last_mode != 0 && last_mode != 1` path that skips the
blend-field reset before setting texture target `0` and clearing distort.

Source-shape note: the native `last_mode` dispatch is VC6's two-case `switch`
idiom (`sub eax, ebx; je; dec eax; jne`), not a plain `if`/`else if` chain.
The scratch also keeps the reused `0x3f800000` value as raw bits because native
stores that same register into `unknown_664`, `primary_blend`, and
`secondary_blend`.
