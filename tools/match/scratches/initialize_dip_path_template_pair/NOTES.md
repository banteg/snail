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

2026-07-15 ownership recovery: the endpoint index is now retained as
`curve_count + 1`, both endpoint sample pairs are initialized through their
owned fields, and the curved middle uses the native explicit sample-byte cursor
and `do/while` lifetime. The middle initializer increments its logical index
between matrix identity and Y/Z placement, then orients the preceding pair.
Together these target-backed changes raise focused Wibo from 30.19% (564/655)
to 33.41% (596/655), while recovering 25 clean masked operands and reducing the
temporary four call mismatches back to the single pre-existing alignment
mismatch.

2026-07-15 mesh ownership recovery: the native acquires `facequads` before
`vertices`, retains an aggregate `Vector3` for ordinary rows, uses a
face-column `do/while`, and contains explicit parity branches even though both
arms currently request the same texture. Preserving those source facts raises
focused Wibo from 33.41% (596/655) to 34.74% (600/655), with 25 clean masked
operands and one mismatch. The remaining audit issue pairs the native first mesh
allocation call with the candidate's second call because the still-shorter
sample-orientation region shifts structural alignment; it is kept visible
rather than hidden with a dummy relocation or reordered behavior.

2026-07-17 live owner-ABI closure: the native tail is `retn 0x18`, the iOS
counterpart is `cRPath::BuildDip(float, int, bool, char*, char*)`, and the
Windows caller supplies the additional final cap-texture argument. Binary
Ninja's stale five-parameter view had shifted the first texture onto the mode
slot, retained a user-authored `char*` at stack `+0x14`, and omitted `+0x18`.
The guarded recreation now owns the exact `Path*` receiver and six stack
arguments through `cap_texture`; direct readback confirms storages `+4..+24`.
This is analysis-only: focused Wibo remains 34.74% (600/655), with 26 clean
masked operands and no unresolved or mismatched operands.
