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

## 2026-07-20 path-lifetime ownership replay

Live Binary Ninja inspection recovers nine complete owners from the remaining
body: primary and secondary basis-right vectors, both terminal deltas, the
primary mesh sample, ordinary and terminal vertices, and the two simultaneous
facequad records. The replay verifies canonical `Vec3`,
`PathTemplateSample`, and `ObjectFaceQuad` layouts before applying their exact
register-variable IDs.

Two tempting forward-vector addresses were rejected. Although each points at a
real preceding-sample member, typing the byte-biased lifetimes introduced eight
backward `__offset` expressions in adjacent position reads. The retained set
previews and exports with zero offsets. No scratch source changed, preserving
the honest 34.74% focused match and 26 clean masked operands.

## 2026-07-26 coupled mesh ownership

Raw instructions at `0x41ea51..0x41eb28` prove distinct ordinary and terminal
mesh owners. The ordinary branch first materializes a lateral-offset vector,
then a generated-position vector, and only then its destination vertex. The
terminal branch separately owns its lateral offset, raised endpoint, generated
position, and terminal destination vertex. Dip's native acquisition order
remains intentionally distinct from Hump and Dump: `facequads` precedes
`vertices`.

The face loop simultaneously proves independent records at `0x41ebf8` and
`0x41ecab`. Each branch owns its face pointer and header word, preserves the
redundant parity-selected texture call, and writes all four UV pairs. Replaying
the complete dependent owner set produces:

```text
match: 38.95%
target: 655 insns, candidate: 644 insns
prefix: 8/655 target insns
masked operands: 30 ok, 0 unresolved, 0 mismatch
```

This raises the focused result by 4.21 points, recovers 44 candidate
instructions and four clean operands, and gives the candidate the exact native
`0x50` frame. The remaining broad alignment drift begins in the earlier sample
construction/orientation region rather than this mesh tail.

## 2026-07-26 Dip count and cursor ownership

Windows raw assembly, IDA Professional 9.4, and the optimized ARM sibling
inspected with Ghidra 12.1.2 agree on the two early aliases. The dead
`width_cells_` argument owns the integer curve count after conversion, while
the consumed `curve_source` argument owns the derived dip radius. IDA also
shows the input stack slots being reused for exactly those values. Keeping
either rewrite in isolation was not sufficient; the coupled aliases raise the
focused result from 38.95% to 39.88%.

The curved middle keeps its current primary and secondary samples owned by
their member arrays and a `0xa8` byte cursor across the identity and cosine
calls. Hoisting those current samples into pointer locals was the main source
of drift. Leaving the array expressions explicit raises the focused result to
50.08%. The preceding samples are different owners: removing their two
explicit pointers regressed the result to 46.13%, so they remain local aliases.

The endpoint and strip-mesh passes likewise expose distinct byte cursors, and
the face loop computes one common record index before selecting one of two
branch-local `ObjectFaceQuad` records. A single face pointer shortened the
candidate by another ten instructions and contradicted the two native
materializations at `0x41ebf8` and `0x41ecab`, so it was rejected despite a
higher scalar score. The retained ownership model produces:

```text
match: 48.89%
target: 655 insns, candidate: 646 insns
prefix: 20/655 target insns
masked operands: 31 ok, 0 unresolved, 0 mismatch
```

This final scalar is lower than the transient current-sample-only result
because the common face index changes global register allocation, but it
extends the exact prefix from 8 to 20 instructions and preserves every audited
relocation. Branch-scoped preceding-sample pointers, a shared face pointer,
explicit delta cursors, direct orientation expansion, and statement-order-only
micro-adjustments were all measured and rejected. No dummy calls, dead
relocations, or equal-arm texture rewrites were introduced.
