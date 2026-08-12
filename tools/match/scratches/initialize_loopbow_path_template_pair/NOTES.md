# Reconstruction notes

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

## Scope

Target: `initialize_loopbow_path_template_pair` at `0x42ba80`, compiled with
MSVC 6.5 using `/O2 /G5 /W3`.

The starter was only a two-instruction stub.  This scratch reconstructs the
complete path-template initializer: constructor fields, two sample arrays, the
loop-bow curve, normalized sample deltas, terminal directions, strip vertices,
face quads, UVs, texture selection, and the finalizer call.

## ABI and layout findings

The native function is a `thiscall` with six stack arguments and `ret 0x18`:

```cpp
float curve_scale,
unsigned int width_cells_arg,
bool mode,
char* texture_a,
char* texture_b,
char* unused_texture
```

The two apparently unused arguments are retained because surrounding native
call sites push six arguments.  The earlier four-argument skeleton could not
reproduce the native epilogue or texture argument slots.

The paired Android and iOS Path.o symbol is
`cRPath::BuildLoopBow(float, int, bool, char*, char*)`. Windows preserves that
portable five-argument prefix and adds the final unused texture slot, proving
that the third stack argument is an authored `bool` even though this build
does not consume it.

The recovered shared owners are intentionally narrow:

- `AttachmentSample` has stride `0xa8`.
- Its transform is at `+0x00`, delta vector at `+0x80`, delta length at
  `+0x8c`, center value at `+0x90`, and loop-bow scalar fields through `+0xa4`.
- `ObjectFaceQuad` has stride `0x30`, five 16-bit vertex/header fields,
  a texture pointer at `+0x0c`, and eight UV floats through `+0x2c`.
- `Path` exposes only the fields used across the recovered constructor family.

Compile-time size checks guard both reconstructed element strides in their
shared headers.

2026-07-14 ownership pass: the builder now consumes
`Object::facequads` directly. The shared facequad's flat UV view preserves the
constructor's native source shape while its `uv[4]` view remains available to
runtime consumers. The focused result stayed at the accepted baseline:

```text
match: 67.54%
target: 796 insns, candidate: 800 insns
masked operands: 60 ok, 0 unresolved, 2 mismatch
```

## Reconstructed behavior

The accepted body follows the native phases in order:

1. Initialize path-template flags and dimensions, derive
   `curve_segment_count = int(curve_scale * 2*pi)`, add fourteen straight
   samples, and allocate both sample arrays.
2. Build seven incoming straight samples and seven outgoing straight samples.
3. Build the circular middle section, including center interpolation, the
   primary and secondary radii, basis-vector construction, the world-Y
   rotation, and the secondary `0.49f` normal offset.
4. Compute and normalize primary and secondary deltas, then construct separate
   `{0, 0, 1}` terminal direction values.
5. Allocate the strip mesh, generate the `(segments + 1) * (width + 1)` vertex
   grid, and synthesize the extra terminal row from the final sample.
6. Emit two `0x30` face quads per cell with the native winding split, UV scale
   of `0.125f`, parity branch, and the two texture arguments.
7. Call `calc_path_length_z(this)`.

2026-06-20 thunk audit: `0x44d1d0` was initially bounded as an anonymous
matrix forwarder. The two aligned calls at `+0x56c` and `+0x57d` were therefore
kept as honest symbolic mismatches until its authored identity could be proved.

## Source-shape decisions

The most productive source-shape changes were:

- correcting the six-argument ABI;
- using direct indexed sample accesses for the two straight sections;
- preserving the native floating-point literal spellings and expression order;
- materializing value `Vector3` objects for arc/delta/mesh calculations;
- constructing distinct primary and secondary terminal direction temporaries;
- retaining a meaningful endpoint vector for the synthetic final mesh row;
- declaring the sample pointer separately inside each vertex-loop branch;
- duplicating face construction in the two side branches instead of merging a
  common face pointer and common tail.

The endpoint and branch-local pointer lifetimes recover the native `0x9c`
local frame without dummy locals or stack padding.  The candidate also ends in
`ret 0x18`, as required by the recovered ABI.

## Remaining differences

The first mismatch is now local-slot allocation rather than control flow:

```text
target[10]    mov [esp+0x2c], esi
candidate[10] mov [esp+0x24], esi
```

The overall frame size is nevertheless exact.  Remaining structural drift is
concentrated in:

- local lifetime/slot ordering in the constructor and arc setup;
- the basis-copy and secondary-offset sequence after the two matrix calls;
- x87 evaluation order and pointer induction in the vertex-grid loop;
- register allocation and duplicated texture/UV stores in the face loop.

No inline assembly, fake globals, volatile clutter, or artificial frame padding
was used.

## Shared Template Type Pass

2026-06-20:

- The sample-backed path-template initializers now include the shared
  `track_attachment_types.h` `Path` instead of duplicating
  local class overlays. The pass covers the 26 initializer scratches that
  already used shared `AttachmentSample`.
- `Path::strip_mesh` is now shared as an `Object*`, matching
  the constructor family evidence: these functions request object vertices and
  facequads, then write `ObjectFaceQuad` grids. The narrow
  `PathTemplateStripMesh` prefix view remains for mirror/finalizer code that
  only needs the `flags` word at `+0x10`.
- The `worm`, `cage2`, and `kind42` initializers intentionally keep their local
  template overlays for now because they still carry local sample/facequad
  aliases that need a separate source-shape pass.
- All 26 promoted initializer scratches kept their exact pre-pass matcher
  results, and the existing non-initializer consumers of
  `track_attachment_types.h` also reran without score drift.

## Next region to attack

The highest-value next pass is the vertex-grid block beginning near target
offset `+0x7d3` (roughly target instructions 515 onward).  Moving the sample
pointer into the two branches produced the final large score gain, which shows
that this region is still highly sensitive to plausible source-level lifetime
and evaluation-order changes.  The next experiments should focus on the row
sample-offset induction, the terminal-row endpoint expression, and preserving
`lateral` on the x87 stack, while leaving the already exact frame and matrix
call positions intact.

## Validation command

```sh
tools/match/match.sh \
  tools/match/scratches/initialize_loopbow_path_template_pair \
  --regions --max-regions 20 --region-context 6
```

2026-07-14 matrix-multiply owner pass: both local-Y rotation compositions now
pass the temporary matrix through the recovered const-reference
`tMatrix::Multiply` member, eliminating the old casts. The
honest partial remains byte-identical at 67.54%, 800/796 candidate/target
instructions and prefix 10/796.

2026-07-24 authored matrix-member closure: Android's adjacent
`tMatrix::Multiply(const tMatrix&)` symbol branches directly to
`tMatrix::operator*=(const tMatrix&)`, proving that Windows' four-instruction
entry at `0x44d1d0` is the authored `Multiply` member and the 18-instruction
body at `0x44d1a0` is the multiply-assignment operator. iOS exports both names
and calls `Multiply` at these same two LoopBow sites. The candidate instructions
are unchanged, while the masked audit closes from 60 clean / 2 mismatched to
62 clean / 0 mismatched operands.

## 2026-07-17 constructor ABI closure

The native tail returns with `retn 0x18`, proving six stack arguments after the
`Path*` receiver. Both world-initializer constructions expose float curve
scale, integer width, a byte mode, two surface textures, and the Windows-only
vertical texture; the iOS `BuildLoopBow` symbol independently preserves the
portable first five types.

Guarded Binary Ninja recreation and readback now recover the full void member
ABI. The shared declaration and scratch also stop returning the finalizer's
incidental EAX state: both are honestly `void`, matching the native caller and
callee contracts. That source correction is byte-identical at 67.54%
(800/796), with the existing 60 clean operands and two multiply-thunk symbol
mismatches at that stage. The later authored matrix-member closure removes both
without changing source behavior or instruction bytes.

## 2026-07-20 staged basis and mesh lifetimes

Transactional Binary Ninja previews now recover nineteen complete owners while
keeping this constructor at zero synthetic `__offset` expressions. The durable
schedule covers both right vectors, the split sample cursors used to derive the
up and forward basis vectors, the primary-up/secondary-position offset step,
both normalized delta vectors, both terminal deltas, the ordinary mesh sample,
ordinary and terminal vertices, and the two simultaneous facequad records.

The terminal mesh branch deliberately computes the synthetic final row from
the previous `0xa8`-byte sample. Typing its byte-biased current-sample cursor as
`PathTemplateSample*` introduced six negative offsets, so that candidate is
rejected rather than disguised. The matcher source remains honest and
unchanged at 67.54% (800/796 instructions), with 60 accepted masked operands
and the two existing multiply-thunk symbol mismatches.

## 2026-07-27 mobile-authored selector type

Promoting the third argument from the earlier byte-width placeholder `char` to
`bool` is byte-identical under VC6. Focused matching remains 67.54%
(800/796 candidate/target instructions), with a 10-instruction exact prefix
and 63 clean masked operands. The change records exact paired Android/iOS
symbol provenance without changing Windows' extra texture slot or imitating
codegen.

## 2026-07-28 mobile-backed control ownership

The exact Android and iOS `cRPath::BuildLoopBow(float, int, bool, char*,
char*)` bodies independently preserve the same portable ownership graph:
derived curve and total sample counts, seven-sample lead and tail passes, the
zero-based curve pass beginning at sample byte offset `7 * 0xa8`, and the
delta-normalization pass. Both ports end at `CalcLengthZ`; neither contains the
Windows strip-mesh and facequad tail.

Windows machine code remains authoritative for all addresses and lifetimes.
A transactional Binary Ninja replay now separates 32 exact MLIL definitions
into eleven logical owners: `curve_segment_count`, `total_segment_count`,
`curve_radius`, and the index/byte-offset pairs for the lead, tail, curve, and
delta passes. Nine already-bounded scalar lifetimes also recover
`center_offset`, the floating curve count, straight-sample Z values, secondary
radius, terminal sample offset, angle, half-angle, and half-sine. The
Windows-only mesh/face counters remain untouched by this mobile-backed pass.

The replay previews and rolls back before applying, saves the database, and is
idempotent on a second run. Strict Binary Ninja/IDA 9.4 export reports zero
symbol mismatches and all 1,142 decompile health checks pass. The candidate
source is intentionally unchanged: focused matching remains 67.54% (796 target
/ 800 candidate instructions), prefix 10/796, with 63 clean masked operands
and no unresolved, mismatched, or unaudited operands. Repository validation is
497 tests passed, exact-only masked audit clean, and extern lint clean.

## 2026-07-30 value ownership and mesh control

An evidence-bounded VC6 source-shape pass improves the focused match from
67.54% (800/796 candidate/target instructions) to 71.88% (801/796). The local
frame remains the native `0x9c`, the exact prefix remains 10 instructions, and
all 63 masked operands remain clean.

The accepted changes are ordinary authored constructs:

- The secondary curve offset is now the value returned by
  `tVector::operator*(float)`, then added through a pointer to the secondary
  position. A five-way mutation sweep raised this block from 68.76% to 69.39%
  and rejected copy-then-scale ownership.
- Each delta is expressed with the recovered binary subtraction operator.
  Both primary and secondary directions are normalized before advancing the
  shared sample index, matching the native loop-carried control order.
- The face loop presents the front face as the `side == 0` fallthrough and the
  back face as the alternate arm. This semantically equivalent winding order
  is the largest mesh-tail gain, raising the complete candidate from 70.26% to
  71.88%.

## 2026-07-30 mesh and face boundary

Raw Windows code and Binary Ninja IL were used to replay the remaining mesh
row schedule as one dependency-closed mutation: guarded row entry, the
`0xa8`-byte sample cursor, ordinary-row fallthrough, and branch-local sample
and vertex owners. That complete native-looking source shape regresses the
accepted 71.88% result to 69.92%, so no fragment of that schedule is retained
without new allocation evidence.

The apparent common face-index value in SSA was also tested as a source owner.
Its declaration and front-face use are byte-neutral, while moving the back
face or both faces through it regresses the focused result as far as 67.04%.
Together with the earlier parity sweep, this bounds the obvious remaining
mesh/face ownership spellings.

The ledger now contains six checked mutation sweeps covering 45 unique
variants: three improving, 31 neutral, and 11 degrading. Its recorded frontier
is **71.88%** (801/796
candidate/target instructions), with the exact `0x9c` frame, a ten-instruction
prefix, and all 63 references clean.
- The synthetic endpoint value is scoped to the terminal-row branch. This is
  byte-neutral but records its actual lifetime.

The bounded negative evidence is retained rather than hidden:

- All four mesh-owner declaration schedules were byte-neutral after correcting
  an initial malformed generated sweep. The earlier compile failures were
  tooling noise caused by literal patch markers, not candidate evidence.
- Reversing the ordinary/terminal row condition fell to 67.46%. Replacing the
  mesh values with scalar components fell to 63.88% and changed the frame from
  `0x9c` to `0x78`.
- Vector operators in the mesh-row calculation lost the smaller subtraction
  gain, so the explicit value constructors remain.
- Hoisting one face pointer and header clear above the side branch fell from
  71.88% to 65.41% and enlarged the frame to `0xa0`; the duplicated
  branch-local owners are therefore retained.
- A complete 24-variant sweep of equivalent parity-condition orientations at
  both texture sites was byte-neutral. Native's out-of-line duplicate texture
  arm cannot be recovered by respelling that condition, and the authored
  parity control is not simplified away.

`experiments.jsonl` validates as four mutation sweeps covering 37 unique
variants with no malformed records or repeats.

## 2026-07-30 mesh arithmetic ownership

The later mesh-family recoveries provide new allocation evidence beyond the
earlier ownership frontier. A complete four-way sweep proves that the
column-relative lateral value is an authored `double` local: it adds 10.33
weighted bytes, reaches 72.24%, and preserves all 63 references. The
expression-only double spelling adds reference debt, the split-float form is
neutral, and the volatile form loses the exact prefix.

An exhaustive 35-variant interaction sweep then isolates one further authored
operator: only the terminal branch scales the previous sample's right vector
with `Vector3::operator*`. That minimal change adds another 7.38 weighted
bytes. The ordinary scale is byte-neutral, both additions are neutral in the
terminal branch and degrading in the ordinary branch, and no multi-site form
beats the single terminal scale.

The retained result is **72.49%**, up 17.71 weighted bytes from 71.88%, with
exactly 796/796 candidate/target instructions, prefix 10/796, the native
`0x9c` frame, and all 63 masked references clean. The expanded ledger now
validates as eight sweeps covering 84 unique variants with no malformed or
repeated records; this evidence supersedes the prior frontier.

## 2026-07-30 scalar stack-coloring boundary

The current target and candidate both contain exactly 796 instructions and use
the native `0x9c` frame, but their early scalar owners occupy different stack
homes. Native places `curve_segment_count_f` and the lead-pass float at
`[esp+0x18]` and `[esp+0x1c]`; the candidate assigns those two values in the
opposite order. The center offset and integer count owners are likewise a
permutation, which cascades into later vector temporary slots.

Ordinary source lifetime changes do not recover that coloring. Four loop- and
function-block placements for the lead float are byte-identical. Six split,
combined, and reordered declaration schedules for the curve, total, and
floating counts are also byte-identical. The allocator is responding to the
full interference graph rather than lexical declaration order.

The adjacent curve-pivot translation is similarly bounded. Compound and
assigned direct Z writes are byte-identical at 72.49%; position or float
pointers lose 120 weighted bytes, and persistent sample pointers lose 378.
The direct operators therefore remain retained. These three non-improving
sweeps close the evidenced scalar-layout neighborhood without register,
volatile, or dummy-lifetime forcing.

## 2026-07-31 direct face-offset record ownership

The earlier common-index probe did not cover the consequential source
boundary: one semantic integer offset consumed directly by every face-record
write. Replacing the two branch-local face pointers with
`facequads[face_offset]` raises focused matching from **72.49%** to **74.31%**
and moves candidate size from 796 to 792 instructions against the
796-instruction target. Prefix remains 10/796 and all 63 references remain
clean.

Four equivalent offset spellings compile byte-identically, so the gain belongs
to direct indexed record ownership rather than expression spelling.

## 2026-07-31 post-face addition bound

The two position-addition boundaries were replayed after direct face
ownership. Terminal `Vector3::operator+` remains byte-neutral at **74.31%**,
792/796 instructions, prefix 10/796, with all 63 references clean. Ordinary
addition instead falls to **74.18%**. The retained component forms preserve
the closer post-face allocation.
