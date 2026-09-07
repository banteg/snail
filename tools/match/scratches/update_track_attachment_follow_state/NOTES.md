# cRPathFollowGoldy::Traverse @ 0x420cb0

Current recovery: semantic-complete; source shape remains open.

Android and iOS `Path.o` independently export the exact authored method
`cRPathFollowGoldy::Traverse(float, tVector&, tVector*)`, with one body on
each platform. Live Windows analysis confirms the same three-argument
thiscall, integer mode return, 0x40-byte `cRPathFollowGoldy` owner, two native
callers, and the complete mode-switch consumer in `cRSubGoldy::AI`.

The matcher now uses the authored method and reference parameter directly.
VC6 emits
`?Traverse@cRPathFollowGoldy@@QAEHMAAUtVector@@PAU2@@Z`; selecting that exact
COFF symbol is byte-neutral at 75.66% (712/726 instructions), with a
122-instruction exact prefix and all 65 relocations resolved cleanly.

Recovered behavior covers path-sample stepping, ordinary and nonlinear
transforms, Goldy matrix publication, side exits, and the Supertramp terminal.
The observed 14-instruction deficit involves block layout, matrix
temporaries, and x87 scheduling; those differences do not establish a compiler
limitation. Recorded experiments preserve the rejected
source-shape frontier; obsolete runnable mutation recipes are not retained.

## 2026-09-05 orientation copy and source-cell ownership

The current baseline before this pass was 76.22%, 712/726 instructions, prefix
122, and all 65 references clean. The retained `orientation_up =
transform.basis_up` assignment recovers the native vector-copy address and
store sequence. Borrowing the complete source `cRSubLoc` in the ordinary path,
rather than its interior position, also recovers native cell-relative field
loads. Together they improve to **77.05%**, with the same 712/726 instruction
count, prefix 122, and all 65 references clean. The six isolated ownership
forms are recorded in `whole-orientation-copy-owners-20260905-mutations.json`.

A coupled vector reconstruction is a useful lead, not a retained match:
representing the ordinary base position as one `Vec3`, using shared vector
operators for offsets, and preserving the output borrow restores the native
base and matrix stack positions and most of the ordinary x87 sequence. The
best owner-reload form reaches 83.86%, but merges native side-exit return
paths and increases the instruction deficit. It is rejected as a tradeoff.

The other six whole-source recipes preserve 86 successful probes: fifteen
vector/output/terminal combinations, 31 owner/reload combinations, thirteen
clamp forms, eight exit branch forms, thirteen vector-value scopes, and six input-X borrows. The
highest 84.28% exit-branch form also loses two audited float-constant
references; no reference rule is changed. Scope and pointer-spelling changes
do not repair the merged-return frontier. These are bounds on the tested
source forms, not evidence of exhaustion.

## 2026-09-07 live sample count and terminal vector composition

Keeping the sample count live and deriving its last index at each comparison
recovers the native count-to-final-index register relationship. The terminal
launch position is now the complete vector expression
`(anchor + terminal.position) + forward_offset`, preserving the two additions
and the caller's final X restoration. These are the same source relationships
independently recovered in the Golb traversal.

Together they improve **77.05% to 78.30%**, with **712/726 instructions**,
**prefix 145** (previously 122), and all **65 references clean**. No frame,
layout, ABI, or shared arithmetic implementation changes.

`coupled-sample-count-and-vector-results-20260907.json` records 15 forms on
the former canonical body and the earlier vector reconstruction. A separate
nonlinear output scalar does not improve the retained combination. The vector
seed with the live count and complete terminal sum reaches 86.79%, prefix 194,
and 65 clean references, but still has only 705/726 instructions and is not
promoted. Its full diff isolates a large deficit in merged side-exit/clamp
returns, alongside nonlinear input/output and normal-bank reload lifetimes.
This remains an active source hypothesis rather than an exact match.

## 2026-09-07 vector results and live sample-array ownership

The vector reconstruction is now retained. The ordinary path uses a complete
base position, right offset, up offset, and final vector sum. Its source and
destination values remain distinct from the terminal launch vector. Both
terminal orientation components read through the live primary sample array;
the second matrix copy similarly reloads the secondary array after copying
the first matrix. Direct indexed sample reads replace the extra cached sample
and cell aliases in the ordinary displacement calculation.

The primary-array reload is the consequential coupling: it restores the native
input lifetime and all three side-exit return tails in the previously rejected
vector reconstruction. Changing the clamp is unnecessary. The indexed
ordinary base then recovers the missing address preparation and removes the
extra cached-array spill. Together the retained source improves **78.30% to
97.25%**, recovers the exact **726/726 instruction count**, extends the prefix
from **145 to 194**, and keeps all **65 references clean**. The separate unused
nonlinear output scalar is neutral after this recovery. Unused decompiler
temporaries are removed and the remaining values are named by their role.

Six recipes record 98 compiling forms across the coupled array/input owners,
nonlinear field and vector publications, vertical/basis phases, coordinate
snapshots, ordinary vector expressions, and the separate nonlinear output.
The final cleaned source independently reproduces code SHA-256
`9f35324208fcafa9d20f8bf7e2a69d7e4dd8f4ab1e870bf646f3422a413ee63c`.

The remaining normalized diff has four regions: the terminal LEA/x87 ordering,
nonlinear position addressing and X/Y publication, the three ordinary-base
addition orders, and the right-offset Y multiplication. The terminal and
right-offset differences also occur in Golb traversal. This is a substantial
partial recovery, not a new exact match; no shared header, ABI, compiler
profile, reference rule, or normalization changes.

## 2026-09-07 output lifetime controls after sample recovery

Seventeen follow-ups test late shared or branch-local output borrows at four nonlinear and two ordinary publication boundaries, plus a shared main-branch reference. Moving the output pointer to a late phase regresses to 85.40-85.95%, even at the native 726-instruction count; some alignments also lose reference audit coverage. A shared reference is neutral at 97.25%. These results support retaining the early main-branch output borrow after the primary/secondary sample recovery; no further source is promoted.
