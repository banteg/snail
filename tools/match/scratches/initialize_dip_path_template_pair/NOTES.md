# `initialize_dip_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41e440`.

It models the compact dip template: first and last flat samples, a cosine-based
downward middle section, adjacent-sample orientation, delta vectors, strip mesh
vertices/faces, and finalization.

This is a starter partial. The unusual native layout around endpoint samples and
VC6 x87 scheduling remains open.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments and
the native tail is `ret 0x18`. Updating the scratch and shared declaration from
the stale four-argument prototype moves focused Wibo from 30.02% (564/655) to
30.19% (564/655), with masked operands unchanged at 30 ok, 0 unresolved, 1
mismatch.

2026-07-03 prologue scheduling cleanup: native begins the `curve_source * 5.0f`
x87 multiply at entry, writes the dip header fields, then performs the integer
curve-count conversion before `width_or_scale` and `segment_count`. The scratch
now preserves that order. Focused Wibo remains 30.19% (564/655), with masked
operands unchanged at 30 ok, 0 unresolved, 1 mismatch, so this is retained as
source-shape documentation rather than a score win.

2026-07-04 middle initializer expansion rejection: expanding the curved middle
sample initializer into direct primary/secondary writes regressed focused Wibo
from 30.19% (564/655) to 23.50% (579/655). The masked audit also dropped from
30 ok, 0 unresolved, 1 mismatch to 28 ok, 0 unresolved, 1 mismatch, with the
remaining call mismatch still pairing native `cosine` against matrix identity
setup. The scratch keeps the shared `initialize_sample_pair` spelling for the
middle loop until the surrounding endpoint/local lifetime is isolated.
