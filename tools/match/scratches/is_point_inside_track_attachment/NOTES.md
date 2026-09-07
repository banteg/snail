# cRPath::SearchPos @ 0x42ca90

Exact Windows member: 111/111 instructions with all six masked operands clean.
Android and iOS independently preserve
`cRPath::SearchPos(tVector, tVector, cRSubLoc*)`.

The method scans the owned secondary samples backward, adds the borrowed
`cRSubLoc` anchor to each sample origin, subtracts that origin from the by-value
probe, and rotates the result through the sample inverse matrix. It returns
true inside the widened x/y lane bounds and the sample's positive z span.

Both Windows laser-projectile calls consume AL as a boolean. The second vector
is unused by this Windows split but remains part of the exact `ret 0x1c` ABI;
dropping it would contradict both native code and the mobile signature. The
stable matcher identity remains `is_point_inside_track_attachment`.

## 2026-09-07 version-verified VC6 controls

Unchanged-source probes under the coherent `msvc6.0` and `msvc6.3` component
sets preserve this function's current normalized instructions and reference
state. The seven-function batch pairs the selector/search residuals with four
exact neighboring controls. No compiler override or source change follows
from this comparison. Component versions, hashes, measured results and the
separate mislabeled VC7-archive check are recorded in
[the compiler-control report](../../compiler-profile-controls-20260907.md).
