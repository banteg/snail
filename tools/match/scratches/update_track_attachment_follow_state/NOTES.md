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
