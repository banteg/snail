Current recovery: **exact**, 322/322 instructions over 1274 native bytes,
with 76 masked references and no audit debt. The September 5 recovery below
supersedes the historical source-shape and compiler-residual claims.

# cRCameraman::AI @ 0x4461d0

Authored `cRCameraman::AI()` over the exact 0xd8-byte follow-camera owner. The
sole Windows caller passes `cRSubGoldy::cameraman` at `cRSubGoldy +0x200` and
immediately consumes its live matrix, FOV, and `force_camera_update` byte.
Binary Ninja confirms a void, no-argument `__thiscall`; Android and iOS each
retain one `cRCameraman::AI()` body in `SubGame.o`.

The method builds the desired camera from the player target, first-row ramp,
track attachment, cutscene pitch, lane lean, exit carryover, and heading. It
then smooths the attachment envelope and FOV, interpolates the live matrix at
`cRSubGame::subgame_rate * 0.3`, and publishes the desired matrix as the next
frame's previous pose. The shared owner layout is live/desired/previous
matrices at `0x00/0x40/0x80`, player and game backlinks at `0xc0/0xc4`, FOV and
snap gate at `0xc8/0xcc`, and lift envelopes at `0xd0/0xd4`.

The scratch exports `?AI@cRCameraman@@QAEXXZ`. It is semantic-complete at
92.86%, 322/322 instructions, prefix 36, with all 76 references clean. Five
recorded sweeps cover 296 variants (285 unique). The best further fuzzy gain
adds an instruction and is rejected; the remaining four regions are bounded
VC6 register and x87 scheduling differences, not open camera semantics.

## 2026-09-05 grouped roll expression and initial player lifetime

One `RotLocalZ` argument now contains the lean and steering roll expression.
Grouping each steering multiply preserves the three native constants and
operations. This recovers the x87 pop and every later attachment-rotation
register lifetime, improving 92.86% to 99.38% without tradeoffs. The ungrouped
expression folds constants and was rejected despite its higher fuzzy score.

The last two mismatches were earlier in the first-row ramp check. Removing
the one-use initial `p` alias and reading `player` directly in the matrix
initialization expression fixes them. The complete body matches 322/322
instructions over 1,274 bytes with all 76 references clean. The shared class
layout, borrowed owners, all call ABIs, and normalization stay unchanged.

The recorded expression, threshold, and ramp-input probes distinguish the
accepted grouped expression/direct initial read from neutral or degrading
local alternatives. No register directive or artificial dependency is used.
